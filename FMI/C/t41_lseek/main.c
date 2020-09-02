// ./main patch.bin f1.bin f2.bin

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	if( argc != 4 ) {
		errx(1, "Not enough argumnets");
	}
	
	char *patch = argv[1];
	char *f1 = argv[2]; 
	char *f2 = argv[3];

	int fd1, fd2, fd3;
	
	struct stat st;
	
	struct triple {
		uint16_t offset;
		uint8_t original;
		uint8_t new;
	};
// check if patch.bin and f1.bin are files with valid format	
	if ( stat(patch, &st) == -1 ) {
		err(2, "Failed to stat");
	}
	if ( (st.st_size % sizeof(struct triple)) != 0 ) {
		warnx("Invalid file %s", patch);
	}
	
	if ( (stat(f1, &st)) == -1 ) {
		err(2, "Failed to stat");
	}
	if ( (st.st_size % sizeof(uint8_t)) != 0 ) {
		warnx("Invalid file %s", f1);
	}

// open patch.bin and f1.bin for reading
	if (( fd1 = open(patch, O_RDONLY)) == -1 ) {
		err(3, "File %s failed to open in read mode", patch);
	}
	if (( fd2 = open(f1, O_RDONLY)) == -1 ) {
		close(fd1);
		err(3, "File %s failed to open in read mode", f1);
	}	
	
// create f2.bin
	if (( fd3 = open(f2, O_CREAT | O_RDWR | O_TRUNC )) == -1 ) {
		close(fd1);
		close(fd2);
		err(4, "File %s failed to create", f2);
	}
// copy f1.bin to f2.bin
	uint8_t b;
	while( read(fd2, &b, sizeof(b)) > 0 ) {
		if ( write(fd3, &b, sizeof(b)) != sizeof(b) ) {
			close(fd1);
			close(fd2);
			close(fd3);
			err(5, "File failed to be written");
		}
	}
	struct triple t;
	
	while( read(fd1, &t, sizeof(t)) > 0 ) {
		if ( lseek(fd3, t.offset, SEEK_SET) == -1 ) {
			close(fd1);	
			close(fd2);
			close(fd3);
			err(6, "Failed to lseek");
		}
		
		read(fd3, &b, sizeof(b));
		if( b == t.original ) {
			if( lseek(fd3, -1, SEEK_CUR ) == -1 ) {
				close(fd1);
                        	close(fd2);
                        	close(fd3);
                        	err(6, "Failed to lseek");
			}
			
			if( write(fd3, &(t.new), sizeof(uint8_t)) != sizeof(uint8_t) ) {
				close(fd1);
                        	close(fd2);
                        	close(fd3);
                        	err(5, "File failed to be written");
			}
		} else {
			err(7, "No such byte/offset in %s", patch);
		}
	}	

	close(fd1);
	close(fd2);
	exit(0);
}
