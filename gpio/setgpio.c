// Compile with: gcc /Programme/GPIO.c -o /Programme/GPIO
 
#include <sys/types.h>                        
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int fd;

char GPIO[3][30] = {"/sys/class/gpio/gpio9/value", 														
					"/sys/class/gpio/gpio10/value", 
					"/sys/class/gpio/gpio11/value"}; 

int main(int argc, char** argv)               													
{
	int res;
	int i;

	printf("Anzahl Argumente: %d\n", argc); 																
	
	for(i = 0; i < argc; i++)																				
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}
		
	if (argc >= 1)    																					                                               
	{
		for(i = 1; i < argc; i++)
		{
			fd = open(GPIO[i-1], O_WRONLY | O_NOCTTY);		//	O_NOCTTY - if terminal device, prevent takeover of process-control											
			res = write(fd, argv[i], 1);																		
			close (fd);																					
	}
	return 0;
}