/*
Реализирайте команда swap, разменяща съдържанието на два файла, подадени като входни параметри.
*/

#define _GNU_SOURCE


#include <stdio.h>
#include <fcntl.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern int errno;

int main(int argc, char* argv[])
{
	int fd;
	const char *filename1 = argv[1];
	const char *filename2 = argv[2];
	int errnum=0;
	
	if ( argc != 3 ) {
		err(1,"Invalid number of files\n");
	}

	
	if( ( fd = renameatx_np(AT_FDCWD, filename1, AT_FDCWD, filename2, RENAME_SWAP) ) == -1 ) {
		errnum=(int)errno;
		fprintf(stderr, "Error: %s\n", strerror( errnum ));
		errx(4, "Files failed to swap\n");
	}

	exit(0);
}
