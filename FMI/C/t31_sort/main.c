#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <unistd.h>


int cmp(const void* a, const void* b) {
	return *((unsigned char*)a) - *((unsigned char*)b);
}

int main(int argc, char* argv[])
{

	if ( argc != 3 ) {
		errx(1, "Not enough arguments\n");
	}

	int fd;
	void *buff;
	struct stat st;

	if ( ( fd = open(argv[1], O_RDONLY )) == -1 ) {
		err(2, "File %s failed to open in read mode\n", argv[1]);
	}
	
	if ( stat(argv[1], &st) == -1 ) {
		close(fd);
		err(3, "Failed to stat\n");
	}

	if ( st.st_size == 0 ) {
		close(fd);
		exit(0);
	}

	buff = malloc(st.st_size);

	if ( buff == NULL ) {
		close(fd);
		errx(4, "Not enough memory\n");
	}

	if ( read(fd, buff, st.st_size) != st.st_size ) {
		close(fd);
		free(buff);
		err(5, "Failed to read from file %s\n", argv[1]);
	}

	qsort(buff, st.st_size, 1, cmp);
	
	int fd2;

	if ( ( fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC ) ) == -1 ) {
		int olderrno = errno;
		free(buff);
		close(fd);
		errno = olderrno;
		err(6, "File %s failed to open in read/write mode\n", argv[2]);
	}
	
	if ( write(fd2, buff, st.st_size) != st.st_size ) {
		free(buff);
		close(fd);
		err(7, "Failed to write in %s\n", argv[2]);
	}

	free(buff);
	close(fd);
	close(fd2);
	exit(0);
	
}
