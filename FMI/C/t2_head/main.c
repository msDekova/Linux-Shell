/*
 Реализирайте команда head без опции (т.е. винаги да извежда на стандартния изход само първите 10 реда от съдържанието на файл подаден като първи параматър)
*/

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	
	int fd;
	char c;
	int count = 0;
	int rd;
	char *filename = argv[1];

	if(argc > 2) {
		errx(1,"Invalid number of aruments\n");
	}

	if( ( fd = open(filename, O_RDONLY) ) == -1 ) {
		err(2,"File failed to open in read mode\n");
	}
	
	while( ( rd = read(fd, &c, 1 ) ) > 0 ) {
		
		if( count == 10 ) {
			break;
		}

		if( c == '\n' ) {
			count++;
		}
		write(1,&c,1);
	} 

	close(fd);
	exit(0);
}
