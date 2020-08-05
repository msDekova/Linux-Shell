/*
	swap two files 
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	
	int fd1,fd2;
	void* buff;
	struct stat st;

	if ( argc != 3 ) {
		errx( 1, "Not enough/too many arguments\n" );
	}	
	
	if ( ( fd1 = open(argv[1], O_RDONLY)) == -1 ) 	{
		err(  2, "File failed to open in read mode\n" );
	}

	if ( ( fd2 = open(argv[2], O_RDONLY)) == -1 )   {
                err(  2, "File failed to open in read mode\n" );
        }
	
	if ( stat(argv[1], &st) == -1 ) {
		close(fd1);
		close(fd2);
		err( 3, "Failed to stat\n" );
	}

	buff = malloc( st.st_size );

	if ( buff == NULL ) {
		close(fd1);
		close(fd2);
		errx(5, "Not enough memory\n");
	}
//// read file1 content into buffer
	if ( read(fd1, buff, st.st_size) != st.st_size ) {
		close(fd1);
		close(fd2);
		free(buff);
		err( 4, "Failed to read from file1\n" );
	}	
	
//// open file1 to rewrite
	if ( ( fd1 = open(argv[1], O_TRUNC | O_WRONLY) ) == -1 ) {
		close(fd1);
		close(fd2);
		free(buff);
		err( 6, "File failed to open in write mode\n" );
	}
	
	char c[4096];
//////// ssize_t [-1;ssize_max]; -1 for err
	ssize_t read_bytes;
	
///// write file2 content to file1
	while( ( read_bytes = read(fd2, &c, sizeof(c)) ) > 0 ) {
		if( write(fd1, &c, read_bytes) != read_bytes ) {
			close(fd1);
			close(fd2);
			free(buff);
			err( 4, "Failed to write in file2\n" );
		}
	}

//// open file2 to rewrite
        if ( ( fd2 = open(argv[2], O_TRUNC | O_WRONLY) ) == -1 ) {
                close(fd1);
                close(fd2);
                free(buff);
                err( 6, "File failed to open in write mode\n" );
        }
	
	if ( write(fd2, buff, st.st_size) != st.st_size ) {
		close(fd1);
                close(fd2);
                free(buff);
                err( 4, "Failed\n" );
	}

	close(fd1);
	close(fd2);
	free(buff);
	exit(0);
}
