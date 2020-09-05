#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
	if(argc != 2) {
		errx(1, "Invaid command");
	}
	
	// mkfifo 
	char *fifo="fifo";
	if(mkfifo(fifo, 0644) == -1){
		err(2, "Failed to fifo");
	}

	int fd;
	if((fd = open(argv[1], O_RDONLY)) == -1 ) {
		err(3, "Failed to open file");
	}

	int fd_fifo;
	if((fd_fifo = open(fifo, O_WRONLY)) == -1) {
		err(3, "Failed to open fifo");
	}
	
	dup2(fd_fifo, 1);
	if (execlp("cat", "cat", argv[1], NULL) == -1 ) {
		close(fd);	
		close(fd_fifo);
		err(4, "Failed to exec");
	}
	
	exit(0);
}
