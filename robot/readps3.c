
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <inttypes.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>





int main( int argc, char *argv[])
{
	FILE *fp;
	uint16_t hex[144];
	int i = 0;
	uint8_t mynew = 0, myold = 0;


	/*DIR *mydir;
	struct dirent *myfile;

	mydir = opendir("/dev/");
	while ((myfile = readdir(mydir)) != NULL)
	{
		printf(" %s ", myfile->d_name);
	}
	closedir(mydir);*/



	if ( ( fp = fopen ( "/dev/hidraw3", "rb")) == NULL) {
		printf ( "could not open file\n");
		return 1;
	}

	while (true) {
		fread ( hex, 1, 49, fp);

		for ( i = 0; i < 30; i++) {
			mynew = hex[1] >> 4;
			//printf ( "%04x %04x \r", hex[1], mynew );

			if(mynew ^ myold){
				myold=mynew;
			}
			printf ( "%04x %04x \r", hex[1], mynew );







		}
		printf("\r");


	}
	fclose (fp);
	return 0;
}