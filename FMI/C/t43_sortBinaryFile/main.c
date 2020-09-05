#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 256

int main(int argc, char* argv[])
{
	if ( argc != 3 ) {
		errx(1, "Not enough/Too many files");
	}
	
	struct stat st;
	if ( stat(argv[1], &st) == -1 ) {
		err(2, "Couldn't stat");
	}	
	if ( st.st_size % sizeof(uint32_t) != 0 ) {
		err(3, "Invalid format of %s file", argv[1]);
	}

	int fd_input, fd_output;

	if((fd_input = open(argv[1], O_RDONLY)) == -1 ) {
		err(4, "File failed to open in read mode");
	}
	if((fd_output = open(argv[2], O_CREAT | O_RDWR | O_TRUNC)) == -1 ) {
		close(fd_input);
		err(5, "File %s failed to create", argv[2]);
	}

	const uint32_t BUF_SIZE=2<<10;
	uint8_t buf[BUF_SIZE];
	uint32_t histogram[SIZE] = { 0 };
	int rd;

	// read from input file and count frequencies of each element in histogram
	while((rd = read(fd_input, &buf, sizeof(buf))) > 0 ){
		for(uint32_t i=0; i<BUF_SIZE; i++) {
			++histogram[buf[i]];
		}
	}

	uint16_t byte = 0;
	ssize_t pos = 0;
	while(byte < SIZE && pos < BUF_SIZE) {
		if(histogram[byte] == 0) {
			byte++;
		} else {
			buf[pos] = byte;
			--histogram[byte];
			pos++;
		}
	}
	
	ssize_t wr = pos;
	if((write(fd_output, &buf, wr)) != wr ) {
		close(fd_input);
		close(fd_output);
		err(6,"Failed to write in %s", argv[2]);
	}

	close(fd_input);
	close(fd_output);
	exit(0);
}
