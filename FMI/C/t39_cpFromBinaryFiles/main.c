// ./main fi.bin f2.bin patch.bin

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

	if(argc != 4) {
		errx(1, "Not enough raguments");
	}
	char *f1 = argv[1];
	char *f2 = argv[2];
	char *patch = argv[3];

	int fd1, fd2, fd3;	
	struct stat st;

	// check if file1 consist only of uint8_t bytes
	if( stat(f1, &st) == -1 ) {
		err(2, "Failed to stat");
	}
	if( (st.st_size % sizeof(uint8_t)) != 0 ) {
		err(3, "File %s is invalid", f1);
	}

	// open file1 and file2 in read mode
	if((fd1 = open(f1, O_RDONLY)) == -1 ) {
		err(4, "File %s failed to open in read mode", f1);
	}
	if((fd2 = open(f2, O_RDONLY)) == -1 ) {
		close(fd1);
		err(4, "File %s failed to open in read mode", f2);
	}

	struct triple {
		uint16_t offset;
		uint8_t original;
		uint8_t new;
	};
	
	if((fd3 = open(patch, O_CREAT | O_RDWR | O_TRUNC)) == -1 ) {
		close(fd1);	
		close(fd2);
		err(5, "File %s failed to create", patch);
	}	
	
	
	uint8_t byte1;
	uint8_t byte2;
	uint16_t offset = 0;
	
	struct triple to_fd3;
	
	while(read(fd1, &byte1, sizeof(byte1))>0 && read(fd2, &byte2, sizeof(byte2))>0 ) {
		if( byte1 != byte2 ) {
			to_fd3.offset = offset;
			to_fd3.original = byte1;
			to_fd3.new = byte2;
	
			if( write(fd3, &to_fd3, sizeof(to_fd3)) != sizeof(to_fd3)) {
				close(fd1);
				close(fd2);
				close(fd3);
				err(6, "Failed to write in %s", patch);
			}
	
			offset++;
		}

	}
	
	close(fd1);
	close(fd2);
	close(fd3);
	exit(0);
}
