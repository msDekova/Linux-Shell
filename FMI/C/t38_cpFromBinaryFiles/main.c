// ./main f1.dat f1.idx f2.dat f2.idx

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	if( argc != 5) {
		errx(1, "Invalid number of arguments from command line");
	}	
	
	struct triple_t {
		uint16_t offset;
		uint8_t length;
		uint8_t reserved;
	};
	
	int fd_dat1, fd_dat2, fd_idx1, fd_idx2;
	struct stat st;

	char *dat1 = argv[1];
	char *idx1 = argv[2];
	char *dat2 = argv[3];
	char *idx2 = argv[4];

	if(( fd_dat1 = open(dat1, O_RDONLY) ) == -1 ) {
		err(2, "File %s failed to open in read mode", dat1);
	}
		
	if( stat(dat1, &st) < 0 ) {
		err(3, "Failed to stat %s", dat1);
	}

/// check if .dat file is binary file 
	if ( (st.st_size % sizeof(uint8_t)) >= 0xFFFF ) {
		errx(4, "Invalid .dat file");
	}
	
	if(( fd_idx1 = open(idx1, O_RDONLY) ) == -1 ) {
		close(fd_dat1);
		err(2, "File %s failed to open in read mode", idx1);
	}

/// check if .idx file is valid
	if ( stat(idx1, &st) <0 ) {
		close(fd_dat1);
		err(3, "Failed to stat %s", idx1);
	}	
	
	if ( st.st_size % sizeof(struct triple_t) != 0 ) {
		errx(5, "Invalid .idx file");
	}

	if (( fd_dat2 = open(dat2, O_WRONLY | O_CREAT | O_TRUNC)) == -1 ) {
		close(fd_dat1);
		close(fd_idx1);
		err(6, "File %s failed to create", dat2);
	}

	if (( fd_idx2 = open(idx2, O_WRONLY | O_CREAT | O_TRUNC)) == -1 ) {
                close(fd_dat1);
                close(fd_idx1);
		close(fd_dat2);
                err(6, "File %s failed to create", idx2);
        }

	struct triple_t tr1;
//???
	struct triple_t tr2 = { 0, 0, 0 };		


	while( read(fd_idx1, &tr1, sizeof(tr1)) == sizeof(tr1) ) {
		if( lseek(fd_dat1, tr1.offset, SEEK_SET) < 0 ) {
			close(fd_dat1);
        		close(fd_idx1);
        		close(fd_dat2);
        		close(fd_idx2);
			err(7, "Failed to lseek");
		}
		
		uint8_t *buf = malloc(sizeof(tr1));
		
		if(!buf){
			close(fd_dat1);
                        close(fd_idx1);
                        close(fd_dat2);
                        close(fd_idx2);
                        err(8, "Not enough space");
		}
	
		int rd;
		if ( (rd = read(fd_dat1, buf, tr1.length*sizeof(uint8_t)) ) != sizeof(uint8_t)*tr1.length ) {
			close(fd_dat1);
                        close(fd_idx1);
                        close(fd_dat2);
                        close(fd_idx2);
                        err(8, "Failed to reed");
		}

		if(buf[0] < 'A' || buf[0] > 'Z') {
			free(buf);
			continue;
		}

		if ( ( write(fd_dat2, buf, tr1.length*sizeof(uint8_t)) ) < 0 ) {
			close(fd_dat1);
                        close(fd_idx1);
                        close(fd_dat2);
                        close(fd_idx2);
                        err(8, "Failed to write");
		}
	
		tr2.length = tr1.length;
		tr2.offset += tr1.length;

		if ( ( write(fd_idx2, &tr2, sizeof(tr2)) ) <0 ) {
			close(fd_dat1);
                        close(fd_idx1);
                        close(fd_dat2);
                        close(fd_idx2);
                        err(8, "Failed to write");
		}

		free(buf);
	}
	
	close(fd_dat1);
	close(fd_idx1);
	close(fd_dat2);
	close(fd_idx2);
	exit(0);
}
