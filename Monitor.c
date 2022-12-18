//ping to specofic ip address and port

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <errno.h>
#include <time.h>

#define MAXLINE 4096
#define SA struct sockaddr

int main()
{
    int sockfd;
  
    struct sockaddr_in servaddr;
    fd_set rset;

    FILE *f = fopen("pings_results_c.txt", "a");
    int counter = 0;
    double avg = 0;

    clock_t start, end;
    double cpu_time_used;



    for (int i=0; i < 100; i++) {

    start = clock();
    counter++;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket error");
        exit(1);
    }

  

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi("80"));
    if (inet_pton(AF_INET, "192.168.248.138", &servaddr.sin_addr) <= 0)
    {
        printf("inet_pton error for %s", "192.168.248.138");
        exit(1);
    }

    FD_ZERO(&rset);
    FD_SET(sockfd, &rset);
  
    

    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect error");
        exit(1);
    }
    else
    {
        printf("connected to %s:%s", "192.168.243.138", "80");
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        avg += cpu_time_used;
        fprintf(f, "Index of ping request %d\n", counter);
        fprintf(f, "Time to take %f Sec\n", cpu_time_used);
        sleep(5);
    }

    }

    double total_avg = avg/counter;
    fprintf(f, "Average time to take %f Sec\n", total_avg);
    fclose(f);

}

