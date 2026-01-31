#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <assert.h>
#include <signal.h>

#include "server_utils.h"

#define TEST_PORT 7123

/**
  * file: test_server.c
  * Contains unit tests for checking the functionality of the server API
  */

char* test_msg = "hello";

void client_action(char* buf, size_t bufsize)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        return;
    }

    struct sockaddr_in targ;
    memset(&targ, 0, sizeof(targ));
    targ.sin_family = AF_INET;
    targ.sin_port = htons(TEST_PORT);
    targ.sin_addr.s_addr = htonl(INADDR_LOOPBACK); 

    sendto(sockfd, test_msg, strlen(test_msg), 0, 
           (struct sockaddr*)&targ, sizeof(targ));

    struct sockaddr_in from;
    socklen_t addrlen = sizeof(from);
    
    int received = recvfrom(sockfd, buf, bufsize - 1, 0, 
                            (struct sockaddr*)&from, &addrlen);
    
    if (received >= 0) {
        buf[received] = '\0'; 
    }

    close(sockfd);
}

int main() 
{
  char cbuf[2048];
  char sbuf[2048];
  memset(cbuf, 0, sizeof(cbuf));
  memset(sbuf, 0, sizeof(sbuf));
  pid_t pid = fork();
  if (pid < 0) 
  {
    perror("fork failed");
    exit(1);
  }

  if (pid == 0) 
  {
    start_server(sbuf, sizeof(sbuf), TEST_PORT);
    exit(0);
  } else {
    sleep(1);
    client_action(cbuf, sizeof(cbuf));
    printf("[Test] Server: PASSED");
    kill(pid, SIGTERM);

    int status;
    waitpid(pid, &status, 0);
    assert( strcmp(cbuf, test_msg) == 0 );
  }

  return 0;
}
