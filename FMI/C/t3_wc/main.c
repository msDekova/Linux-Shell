/*
Реализирайте команда wc, с един аргумент подаден като входен параметър
*/

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	
	int fd;
	char c;
	int lines = 0;
	int words = 0;
	int chars = 0;
	const char* filename = argv[1];
	int rd;

	if( argc != 2 ) {
		errx(1,"Invalid number of arguments\n");
	}

	if ( (fd = open(filename, O_RDONLY) ) == -1 ) {
		err(2, "File failed to open in read mode\n");
	}

	while ( ( rd = read(fd, &c, 1) > 0 ) ) {
		if ( c == '\n' ) {
			lines++;
			words++;
		}

		if ( c == ' ' ) {
			words++;
		}

		chars++;
	}

	close(fd);
	printf("%d   %d   %d  %s\n", lines, words, chars, filename);
	exit(0);
}
