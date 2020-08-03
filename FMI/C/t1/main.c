/*
Копирайте съдържанието на файл1 във файл2
*/

#include <fcntl.h>
#include <err.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
	int f1,f2;
	char c;
	char *filename=argv[1];
	if(argc<2){
		err(1,"Invalid number of files");
	}
	
	if( (f1 = open(filename,O_RDONLY) ) == -1) {
		err(2,"File failed to open in read mode\n");
	}

	if( (f2 = open("bar.txt", O_CREAT|O_WRONLY, S_IRUSR | S_IWUSR) ) == -1) {
		err(3,"File failed to open in write mode\n");
	}

	while( read(f1, &c, 1) ){
		write(f2, &c, 1);
	}

	close(f1);
	close(f2);
	exit(0);
}
