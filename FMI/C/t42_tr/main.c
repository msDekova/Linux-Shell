// echo "asdf" | ./main -d 'd123' | ./main 'st' 'fm' | ./main -s 'f' -> af

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void tr_d(const char* str);
void tr_s(const char* str);
void tr(const char* str1, const char* str2);

int main(int argc, char* argv[]) 
{
	if ( argc < 2 ) {
		errx(1, "Not enough arguments for tr command");
	}
	
	if ( !strcmp(argv[1], "tr") ) {
		errx(2, "%s should be tr", argv[1]);
	}

	const char* argv1 = argv[1];
	const char* argv2 = argv[2];
	
	if( strcmp(argv1, "-d") == 0 ) {
		tr_d(argv2);
	} else if ( strcmp(argv1, "-s") == 0 ) {
		tr_s(argv2);
	} else {
		if ( argc != 3 ) {
			 errx(1, "Not enough arguments for tr command");
		} 

		tr(argv1, argv2);		
	}

	exit(0);
}

void tr_d(const char* str) {
	char to_rem[256] = { 0 };
	
	for(int i=0; i<sizeof(str); i++) {
		to_rem[(int)str[i]] = 1;
	}

	char c;
	while( read(0, &c, sizeof(c)) == sizeof(c) ) {
		if ( to_rem[(int)c] == 0 ) {
			write(1, &c, sizeof(c));
		}
	}
}

void tr_s(const char *str) {
	char to_rem[256] = { 0 };

	for(int i=0; i<sizeof(str); i++) {
                to_rem[(int)str[i]] = 1;
        }

	char c, prev;

	read(0, &c, sizeof(c));
	prev = c;
	
	write(1, &c, sizeof(c));
	while( read(0, &c, sizeof(c)) == sizeof(c) ) {
		if(c != prev) {
			write(1, &c, sizeof(c));
		}
		prev = c;
	}
}

void tr(const char* set1, const char* set2) {
        if (strlen(set1) != strlen(set2)) {
                errx(3, "set1 and set2 must have equal size");
        }

        char rem[256];
        for (size_t i = 0; i < 256; i++) {
                rem[i] = (char) i;
        }

    for (size_t i = 0; i < strlen(set1); i++) {
        rem[(int) set1[i]] = set2[i];
    }

        char c;
    while (read(0, &c, sizeof(c)) == sizeof(c)) {
                write(1, &rem[(int) c], sizeof(rem[(int) c]));
    }
}
