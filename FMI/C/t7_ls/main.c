/*
 T2 - Да се напише програма на C, която изпълнява команда ls с точно един аргумент.
*/


#include <err.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if(argc != 2) {
		errx(1, "Need more/less arguments\n");
	}	

	if( ( execl("/bin/ls", "ls", argv[1], (char*)NULL ) ) == -1 ) {
		err(2, "Couldn't exec\n");
	}

	exit(0);
}
