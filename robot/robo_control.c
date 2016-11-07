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
#include <pthread.h>


int fd, fd2, sockfd;
uint8_t emergestop = 0;

char Input;
int i;
int res, x = 0;
int ps3 = 1;


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

  if (ch != EOF)
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

void INThandler() {
  exit(0);
}
void *thread(void *arg) {
  char buffer[256];
  uint16_t value, med[5], median, index;
  int n;
  printf("wallthead running\n");
  while (1) {
    bzero(buffer, 256);

    n = read(sockfd, buffer, 2);
    if (n < 0)
    {
      perror("ERROR reading from socket");
      exit(1);
    }

    value = atoi(buffer);
//printf("%d\n",value);
    index++;
    if (index >= 5)index = 0;
    med[index] = value;
    median = (med[0] + med[1] + med[2] + med[3] + med[4]) / 5;
//printf("value:%d\n",value);
    if (median < 17)if ((value < 10) && (value > 5)) {
        printf("%d stop!\n", value);

        strcpy(buffer, "0\n");
//usleep(100000);
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {error("ERROR writing to socket");}

      }
  }

}

int main(int argc, char** argv)
{
  int  portno, n, foo;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char* strings[] = {"hello ", "world\n"};
  pthread_t thread1;
//pthread_init();

  char buffer[256];
  if (argc != 5) {
    fprintf(stderr, "usage %s hostname port devicepath PS3(0/1)\n", argv[0]);
    exit(0);
  }
  portno = atoi(argv[2]);
  foo = atoi(argv[4]);
  if (foo == 1 || foo == 0) {ps3 = foo;}
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket");
  server = gethostbyname(argv[1]);
  if (server == NULL) {
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR connecting");


  char devname[] = "/dev/input/by-id/usb-_USB_Keyboard-event-kbd";
  int device = open(argv[3], O_RDONLY);
  struct input_event ev;

  signal(SIGINT, INThandler);

  pthread_create(&thread1, NULL, thread, strings);


  //####PS3-control#####################################
  FILE *fp;
  uint16_t hex[50];
  int val = 0 , old = 0, send = 0;
  if (ps3) {
    if ( ( fp = fopen ( argv[3], "rb")) == NULL) {
      printf ( "could not open file\n");
      return 1;
    }
  }



  int w = 0, a = 0, s = 0, d = 0, last = 0;
  while (1)
  {
    if (ps3) {
      fread ( hex, 1, 49, fp);
      val = (0x0f & (hex[1] >> 4));

      if (( (0x01 & (val >> 0)) + (0x01 & (val >> 1)) +  (0x01 & (val >> 2)) + (0x01 & (val >> 3))) > 1 ) {
        if (old != val) {
          send = old ^ val;
        }
      } else {
        send = val;
      }
      old = val;

      switch (send) {
      case 1 : strcpy(buffer, "DRUC\n"); //w
        break;
      case 8 : strcpy(buffer, "DREC\n"); //a
        break;
      case 4 : strcpy(buffer, "DVOR\n"); //s
        break;
      case 2 : strcpy(buffer, "DLIN\n"); //d
        break;
      default : strcpy(buffer, "0\n"); //d

      }
      n = write(sockfd, buffer, strlen(buffer));
      if (n < 0) {error("ERROR writing to socket");}


    } else {

      read(device, &ev, sizeof(ev));
      while (((ev.value == 458778 || ev.value == 458756 || ev.value == 458774 || ev.value == 458759) && (ev.type == 4)) == 0) {
        read(device, &ev, sizeof(ev));
      }
      switch (ev.value) {
      case 458778 : if (w) {w = 0;} else {w = 1; last = ev.value;} //w
        break;
      case 458756 : if (a) {a = 0;} else {a = 1; last = ev.value;} //a
        break;
      case 458774 : if (s) {s = 0;} else {s = 1; last = ev.value;} //s
        break;
      case 458759 : if (d) {d = 0;} else {d = 1; last = ev.value;} //d
        break;
      }
      printf("%d %d %d %d %d \n", w, a, s, d, last );
      if (w + a + s + d) {
        if (w + a + s + d > 1) {
          switch (last) {
          case 458778 : strcpy(buffer, "DRUC\n"); //w
            break;
          case 458756 : strcpy(buffer, "DREC\n"); //a
            break;
          case 458774 : strcpy(buffer, "DVOR\n"); //s
            break;
          case 458759 : strcpy(buffer, "DLIN\n"); //d
            break;
          }
        } else {
          if (w) {strcpy(buffer, "DRUC\n");}
          if (a) {strcpy(buffer, "DREC\n");}
          if (s) {strcpy(buffer, "DVOR\n");}
          if (d) {strcpy(buffer, "DLIN\n");}
        }
      } else {

        strcpy(buffer, "0\n");
      }
      // usleep(500000);
      n = write(sockfd, buffer, strlen(buffer));
      if (n < 0) {error("ERROR writing to socket");}
    }
  }
  close(sockfd);
  fclose (fp);
  return 0;
}
