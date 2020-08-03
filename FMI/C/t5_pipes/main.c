// cat /etc/passwd | sort | uniq

// 0   1   2
// in  out err

/*
	init1
	fork
		child 'cat'
	init2
	fork
		child 'sort'
	init3
	
	'uniq'
*/

#include <unistd.h>
#include <err.h>
#include <string.h>

int main(int argc, char* argv[])
{
	
	int a[2];
	
	if( pipe(a) == -1 ) {
		err(1,"Invalid pipe arr\n");
	}

	pid_t p = fork();

	if( p == -1 ) {
		err(2, "Couldn't fork\n");
	}
	
	// CAT
	if ( p == 0 ) {
		close(a[0]);

		dup2(a[1],1);	

		if ( execlp("cat","cat","foo.txt",NULL) == -1 ) {
			err(3, "Failed cat command\n");
		}

	}

	close(a[1]);
///	dup2(a[0], 0);
	

	int b[2];
	pipe(b);
	int p2 = fork();

	if( p2 == -1 ) {
                err(2, "Couldn't fork\n");
        }

	// SORT
	if (p2 == 0 ) {
		/// read from a[0]
		dup2(a[0],0);
		
		close(b[0]);

		/// write to b[1]
		dup2(b[1],1);
		if ( execlp("sort", "sort", NULL) == -1 ) {
			err(3, "Failed sort command\n");
		}	
	}

	//read from b1 => close b1
	close(b[1]);
	dup2(b[0],0);

	// UNIQ
	if ( execlp("uniq", "uniq", NULL) == -1	) {
		err(4, "Failed uniq command\n");
	}
}
