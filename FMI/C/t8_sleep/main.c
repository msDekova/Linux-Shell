/*
T3 - Да се напише програма на C, която изпълнява команда sleep (за 60 секунди).
*/


#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

int main()
{
	if( execl("/bin/sleep", "command", "60" , (char*)NULL) == -1 ) {
		err(2, "Failed\n");
	}

	exit(0);
}
