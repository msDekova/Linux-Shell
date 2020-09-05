// ./main file -> cat file | sort | tail

#include <unistd.h>
#include <stdlib.h>
#include <err.h>


int main(int argc, char* argv[]) 
{
	if(argc != 2) {
		errx(1, "Invalid command");
	}
	
	int a[2];
	if(pipe(a) == -1 ){
		err(2, "Failed to pipe");
	}
	
	pid_t p1 = fork();
	if( p1 == -1 ) {
		err(3, "Failed to fork");
	}

	// child process == 0
	if ( p1 == 0 ) {
		// close file descriptor for reading
		// the process will only write
		close(a[0]);
		
		// close standart fd for output and redirect new fd for output
		dup2(a[1],1);

		if(execlp("cat", "cat", argv[1], NULL) == -1) {
			err(4, "Failed to exec cat command");
		}
	}
	
	// close fd for writing
	close(a[1]);
	
	int b[2];
	if( pipe(b) == -1) {
		err(2, "Failed to pipe");
	}

	pid_t p2 = fork();
	if ( p2 == 0 ) {
		// close fd for reading
		close(b[0]);
		// read from a[0] not from standart input
		dup2(a[0], 0);
		// write to b[1] not to standart output
		dup2(b[1], 1);

		if(execlp("sort", "sort", NULL) == -1) {
			err(4, "Failed to exec sort command");
		}
	}	
	
	// close fd for writing
	close(b[1]);
	// read from b[0], close standart input
	dup2(b[0],0);
	if(execlp("tail", "tail", NULL) == -1) {
		err(4, "Failed to exec head command");
	}
	
	exit(0);
}
