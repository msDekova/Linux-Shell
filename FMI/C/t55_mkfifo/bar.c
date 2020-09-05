#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>



int main(int argc, char* argv[])
{
	if(argc != 2 ){
		errx(1, "Invalid command");
	}

/*	char* fifo = "fifo";
	if(mkfifo(fifo, 0644) == -1 ) {
		err(2, "Failed to fifo");
	}

	struct stat st;
	if(stat(fifo, &st) == -1){
		err(3, "Failed to stat");
	}
*/	
	int fd;
	if((fd = open("fifo", O_RDONLY)) == -1 ){
		err(4, "Failed to open mkfifi");	
	}
	
	dup2(fd, 0);

	if(execlp(argv[1], argv[1], NULL) == -1) {
		close(fd);
		err(5, "Failed to %s", argv[1]);
	}

	close(fd);
	exit(0);
}
