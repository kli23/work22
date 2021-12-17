#include "pipe_networking.h"
#include <signal.h>

char* toUpper(char input[]) {
  char* start = input;
  int i;
  for (i = 0; i < strlen(input); i++) {
    if (input[i] >= 'a' && input[i] <= 'z')
      input[i] -= 32;
    }
  return start;
}

static void sighandler(int signo) {
  if ( signo == SIGINT )
  printf("Exiting and removing WKP\n");
  remove(WKP);
  exit(0);

}




int main() {
  signal(SIGINT, sighandler);
  int to_client;
  int from_client;
  char clientmsg[BUFFER_SIZE];

  
  while (1) {
    from_client = server_setup();
    printf("[server]: Creating subserver\n");
    int a = fork();
    

    if (a == 0) {
      to_client = server_connect(from_client);

      while (1) {
        read(from_client, clientmsg, BUFFER_SIZE);
        printf("Processing\n");
        toUpper(clientmsg);
        write(to_client, clientmsg, BUFFER_SIZE);
      }
      return 0;
    }
  }
  remove(WKP);


  /*while (1) {
    from_client = server_handshake( &to_client );

    
    char clientmsg[BUFFER_SIZE];

    while (read(from_client, clientmsg, BUFFER_SIZE)) {
      printf("Processing\n");
      toUpper(clientmsg);
      write(to_client, clientmsg, BUFFER_SIZE);
    }
  } */


}