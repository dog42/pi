// Compile with: gcc /Programme/GPIO.c -o /Programme/GPIO

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int fd, fd2;

char GPIO[4][30] = {
    "/sys/class/gpio/gpio23/value", // Array für die GPIOs
    "/sys/class/gpio/gpio25/value",
    "/sys/class/gpio/gpio24/value",
    "/sys/class/gpio/gpio8/value"
};

char dir[5][4][2] = {
    {"0", "0", "0", "0"},  //STOP  = 0
    {"0", "1", "0", "1"},   //ZURÜCK= 1
    {"1", "0", "1", "0"},   //VOR   = 2
    {"1", "0", "0", "1"},   //LINKS = 3
    {"0", "1", "1", "0"}
};  //RECHTS= 4

char Input;
int i;
int res, x = 0;

int gpiowrite(int d) {
    int i;
    if (0 <= d && d < 5) {
        for (i = 0; i < 4; i++)
        {
            fd = open(GPIO[i], O_WRONLY | O_NOCTTY);// Datei mit der Indexnummer "i-1" öffnen und Name unter "fd" speichern
            res = write(fd, dir[d][i], 1);      // Argument mit der Nummer "i" in die geöffnete Datei schreiben
            close (fd);             // Datei schließen
        }
        return 1;
    }
    else return 0;
}



int main( int argc, char *argv[] )
{
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int  n, pid;


    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 5001;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }
    /* Now start listening for the clients, here
     * process will go in sleep mode and will wait
     * for the incoming connection
     */
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    printf("warte auf Verbindung an PORT: %d  ...\n", portno);
    while (1)
    {
        newsockfd = accept(sockfd,
                           (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
        {
            perror("ERROR on accept");
            exit(1);
        }
        else
        {
            printf("VERBUNDEN\n");
        }
        /* Create child process */
        pid = fork();
        if (pid < 0)
        {
            perror("ERROR on fork");
            exit(1);
        }
        if (pid == 0)
        {
            /* This is the client process */
            close(sockfd);
            doprocessing(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    } /* end of while */
}

int doprocessing (int sock)
{
    int n;
    char buffer[256];

    while (1) {
        bzero(buffer, 256);

        n = read(sock, buffer, 255);
        if (n < 0)
        {
            perror("ERROR reading from socket");
            exit(1);
        }




        if (strncmp(buffer, "DVOR", 4) == 0)
        {   gpiowrite(2);
            //sleep(1);
            printf("%s\n", buffer);
        }
        else if (strncmp(buffer, "DLIN", 4) == 0)
        {   gpiowrite(3);
            //sleep(1);
            printf("%s\n", buffer);
        }
        else if (strncmp(buffer, "DREC", 4) == 0)
        {   gpiowrite(4);
            //sleep(1);
            printf("%s\n", buffer);
        }
        else if (strncmp(buffer, "DRUC", 4) == 0)
        {   gpiowrite(1);
            //sleep(1);
            printf("%s\n", buffer);
        }

        else {
            gpiowrite(0);
            //sleep(1);
            printf("%s\n", buffer);
        }




        printf("Here is the message:%s\n", buffer);
    }
}





