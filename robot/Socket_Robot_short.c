// Compile with: gcc /Programme/GPIO.c -o /Programme/GPIO

#include <...>
...


char GPIO[4][30] = {
    "/sys/class/gpio/gpio22/value",
    "/sys/class/gpio/gpio27/value",
    "/sys/class/gpio/gpio17/value",
    "/sys/class/gpio/gpio4/value"
}

char dir[5][4][2] = {    {"0", "0", "0", "0"},  //STOP   = 0
    {"0", "1", "0", "1"},   //BACK   = 1
    {"1", "0", "1", "0"},   //FORWARD= 2
    {"1", "0", "0", "1"},   //LEFT   = 3
    {"0", "1", "1", "0"}
};  //RIGHT  = 4

char Input;
int i, res, x = 0, fd, fd2;

int gpiowrite(int d) {
    int i;
    if (0 <= d && d < 5) {
        for (i = 0; i < 4; i++)
        {
            fd = open(GPIO[i], O_WRONLY | O_NOCTTY);// file index "i" load to "fd"
            res = write(fd, dir[d][i], 1);      // write dir "i"
            close (fd);
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







    /* listening for clients, process will go to sleep mode*/
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    printf("W8 4 connect on PORT: %d  ...\n", portno);
    while (1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
        {
            perror("ERROR on accept"), exit(1);
        }
        else
        {
            printf("connected\n");
        }
        /* a child will be born */
        pid = fork();
        if (pid < 0)
        {
            perror("ERROR on fork"), exit(1);
        }
        if (pid == 0)
        {
            /* Here is the child */
            close(sockfd);
            doprocessing(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    }
}




void doprocessing (int sock)
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




        if     (strncmp(buffer, "DVOR", 4) == 0)    { gpiowrite(2); }

        else if (strncmp(buffer, "DLIN", 4) == 0)    { gpiowrite(3); }

        else if (strncmp(buffer, "DREC", 4) == 0)    { gpiowrite(4); }

        else if (strncmp(buffer, "DRUC", 4) == 0)    { gpiowrite(1); }

        else                    { gpiowrite(0); }
    }





