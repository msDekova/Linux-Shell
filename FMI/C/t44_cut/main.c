// ./main -c n/n-m || ./main -d 'str' -f n/n-m

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void cut_c(const char*);
void cut_d(const char*, const char*);

int main(int argc, char* argv[])
{
	if ( argc != 3 && argc!=5 ) {
		errx(1, "Not enough arguments for cut command");
	}

	const char *arg = argv[1];

	if( strcmp(arg, "-c") == 0 ) {
		cut_c(argv[2]);
	} else if ( strcmp(arg, "-d") == 0 && strcmp(argv[3], "-f") == 0 ) {
		cut_d(argv[2], argv[4]);
	} else {
		errx(2, "Please input valid command -c/-d");
	}

	exit(0);
}

void cut_c(const char* arg) {
	
	int min, max;
	
	if ( strlen(arg) == 1 ) {
		min = arg[0] - '0';
		max = min;	
	} else if ( strlen(arg) == 3 ) {
		min = arg[0] - '0';
		max = arg[2] - '0';
	}
	
	if ( (min < 1 || min > 9) || (max < 1 || max > 9) || (min > max) ) {
		warnx("Invalid number limits");
	}	

	char c;
	int count=0;

	while( read(0, &c, sizeof(char)) > 0 ) {
		++count;

		if(count == min && count <= max) {
			write(1, &c, sizeof(char));	
			++min;
		}		
	}
	
}

void cut_d(const char* argv2, const char* argv4) {
	int min, max;

        if ( strlen(argv4) == 1 ) {
                min = argv4[0] - '0';
                max = min;
        } else if ( strlen(argv4) == 3 ) {
                min = argv4[0] - '0';
                max = argv4[2] - '0';
        }

	char delimiter = argv2[0];

	int count = 0;
	char c;

	while( read(0,&c,sizeof(char)) > 0) {

		if(count == min-1 && count < max) {
			if(c == delimiter) {
				min += 1;
			}
			write(1,&c,sizeof(char));
		}


		if( c == delimiter ) {
			++count;
		}
	}	
}
