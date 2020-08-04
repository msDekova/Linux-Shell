/*
* fork(2) `pid_t fork(void);`
* T4 - Да се напише програма на C, която създава процес дете и демонстрира принцина на конкурентност при процесите.

* wait(2) `pid_t wait(int *wstatus);`
* T5 - Да се напише програма на C, която е аналогична на горния пример, но принуждава бащата да изчака сина си да завърши.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <err.h>

int main()
{
	int status;

	pid_t p = fork();

	if ( p == -1 ) {
		err(1, "Couldn't fork\n");
	}
	
	if ( p == 0 ) {
		for(int i=0; i<10; i++) {
			printf("child\n");
		}
		exit(0);
	}

	wait(&status);
	for(int i=0; i<10; i++) {
		printf("parent\n");
	}

	exit(0);
}
