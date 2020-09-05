#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
	if(argc != 3) {
		errx(1, "Invalid command");
	}
	
	int fd1, fd2;

	if((fd1 = open(argv[1], O_RDONLY) ) == -1){
		err(3, "Couldn't open file");
	}
	if((fd2 = open(argv[2], O_CREAT | O_RDWR | O_TRUNC)) == -1 ){
		close(fd1);
		err(4, "Couldn't create file");
	}

	int a[2];
	if( pipe(a) == -1) {
		err(2, "couldn't pipe");
	}

	pid_t p1 = fork();
	if(p1 == -1 ) {
		err(2, "Couldn't fork");
	}	
	
	if (p1 == 0) {
		close(a[0]);
		dup2(a[1],1);

		if(execlp("xxd", "xxd", argv[1], NULL) == -1){
			err(5, "Failed command");
		}
	}
	close(a[1]);
	dup2(a[0],0);

	uint8_t byte;
	while(read(0, &byte, sizeof(byte)) > 0) {
		if( byte == 0x55 ) {
			continue;
		}
		if( byte == 0x7D && ++byte != NULL) {
			byte ^= 20;
		}
		write(fd2, &byte, sizeof(byte));
	}	
	
	close(fd1);
	close(fd2);
	exit(0);
}
