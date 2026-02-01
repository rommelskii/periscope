#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "log.h"
#include "log_serialize.h"
#include "server_utils.h"

int main(void)
{
  const int PSC_PORT = 7123; //< just for testing

  int sockfd;
  uint8_t buf[2048];
  struct sockaddr_in serv, cli;
  socklen_t addrlen = sizeof(cli);

  log_t recv_log = {0};

  memset(buf, 0, sizeof(buf));

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  serv.sin_family = AF_INET;
  serv.sin_port = htons(PSC_PORT);
  serv.sin_addr.s_addr = INADDR_ANY;

  bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));

  printf("Running Periscope server at port %d\n", PSC_PORT);

  int bytes_received = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&cli, &addrlen);
  if (bytes_received < 0)
  {
    perror("recvfrom failed");
    return -1;
  } 

  printf("Received %d bytes\n\n", bytes_received);

  deserialize_log(&recv_log, buf);

  print_log(&recv_log);
  return 0;
}
