// Compile with: gcc /Programme/GPIO.c -o /Programme/GPIO

#include <sys/types.h>                        
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <linux/input.h>
#include <signal.h>



int fd,fd2;

char Input;
int i;
int res,x=0;


int kbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}
	return 0;
}

void error(const char *msg)
{
  perror(msg);
  exit(0);
}

void INThandler(){
  exit(0);
}


int main(int argc, char** argv)     
{
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];
  if (argc < 3) {
   fprintf(stderr,"usage %s hostname port\n", argv[0]);
   exit(0);
 }
 portno = atoi(argv[2]);
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) 
  error("ERROR opening socket");
server = gethostbyname(argv[1]);
if (server == NULL) {
  fprintf(stderr,"ERROR, no such host\n");
  exit(0);
}
bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
bcopy((char *)server->h_addr, 
 (char *)&serv_addr.sin_addr.s_addr,
 server->h_length);
serv_addr.sin_port = htons(portno);
if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
  error("ERROR connecting");


char devname[] = "/dev/input/by-id/usb-_USB_Keyboard-event-kbd";
int device = open(devname, O_RDONLY);
struct input_event ev;

signal(SIGINT, INThandler);





  int w=0,a=0,s=0,d=0,last=0;
while(1)
{





  // read(device,&ev, sizeof(ev));
  // while(((ev.value==458778 || ev.value==458756|| ev.value==458774||ev.value==458759)&&(ev.type==4))==0){
  //   read(device,&ev, sizeof(ev));
  // }
  // int rev=ev.value;
  // switch(ev.value){
  //       case 458778 : strcpy(buffer,"DVOR\n"); //w
  //       break;
  //       case 458756 : strcpy(buffer,"DREC\n"); //a
  //       break;
  //       case 458774 : strcpy(buffer,"DRUC\n"); //s
  //       break;
  //       case 458759 : strcpy(buffer,"DLIN\n"); //d
  //       break;
  //     }
  //     n = write(sockfd,buffer,strlen(buffer));
  //     if (n < 0) {error("ERROR writing to socket");}

  //     // a-458756
  //     // s-458774
  //     // d-458759

  //     printf("los\n");
  //     read(device,&ev, sizeof(ev));
  //     while(((ev.value==458778 || ev.value==458756|| ev.value==458774||ev.value==458759)&&(ev.type==4))==0){
  //      read(device,&ev, sizeof(ev));
  //     }
  //    strcpy(buffer,"0\n");
  //    n = write(sockfd,buffer,strlen(buffer));
  //    if (n < 0) {error("ERROR writing to socket");}
  //    printf("stop\n");


  read(device,&ev, sizeof(ev));
  while(((ev.value==458778 || ev.value==458756|| ev.value==458774||ev.value==458759)&&(ev.type==4))==0){
    read(device,&ev, sizeof(ev));
  }
  switch(ev.value){
        case 458778 : if(w){w=0;}else{w=1; last=ev.value;} //w
        break;
        case 458756 : if(a){a=0;}else{a=1; last=ev.value;} //a
        break;
        case 458774 : if(s){s=0;}else{s=1; last=ev.value;} //s
        break;
        case 458759 : if(d){d=0;}else{d=1; last=ev.value;} //d
        break;
  }
  printf("%d %d %d %d %d \n",w,a,s,d,last );
  if(w+a+s+d){
    if(w+a+s+d > 1){
      switch(last){
        case 458778 : strcpy(buffer,"DVOR\n"); //w
        break;
        case 458756 : strcpy(buffer,"DREC\n"); //a
        break;
        case 458774 : strcpy(buffer,"DRUC\n"); //s
        break;
        case 458759 : strcpy(buffer,"DLIN\n"); //d
        break;
      }
    }else{
      if(w){strcpy(buffer,"DVOR\n");}
      if(a){strcpy(buffer,"DREC\n");}
      if(s){strcpy(buffer,"DRUC\n");}
      if(d){strcpy(buffer,"DLIN\n");}
    }
  }else{

    strcpy(buffer,"0\n");
  }   
  // usleep(500000);
      n = write(sockfd,buffer,strlen(buffer));
      if (n < 0) {error("ERROR writing to socket");}
}
   close(sockfd);
   return 0;
 }