#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "log.h"
#include "log_serialize.h"
#include "server_utils.h"
#include "file_utils.h" 

int main(void)
{
  const int PSC_PORT = 7123; //< just for testing

  int sockfd;
  uint8_t buf[2048];
  char ip[INET_ADDRSTRLEN];
  struct sockaddr_in serv, cli;
  socklen_t addrlen = sizeof(cli);

  log_t recv_log = {0};

  memset(buf, 0, sizeof(buf));
  memset(ip, 0, sizeof(ip));

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  serv.sin_family = AF_INET;
  serv.sin_port = htons(PSC_PORT);
  serv.sin_addr.s_addr = INADDR_ANY;

  bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));

  printf("Running Periscope server at port %d\n", PSC_PORT);

  char cbuf[FILE_MAXSIZE]; 
  memset(cbuf, 0, sizeof(cbuf));

  FILE* pconf = fopen(FILE_CONF_PATH, "r");
  if (pconf == NULL)
  {
    fprintf(stderr, "File configuration error: cannot load configuration file\n");
  }

  fgets(cbuf, sizeof(cbuf), pconf);
  if(strnlen(cbuf, FILE_MAXSIZE) == 0) 
  {
    fprintf(stderr, "File configuration error: empty configuration file\n");
    return 1;
  }

  printf("Configuration file loaded from %s\n", FILE_CONF_PATH);
  printf("Logging file loaded from %s\n", cbuf);
  
  for (;;) 
  {
    int bytes_received = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&cli, &addrlen);
    if (bytes_received < 0)
    {
      perror("recvfrom failed");
      return 1;
    } 

    deserialize_log(&recv_log, buf);

    /**
    * Begin file handling stuff here
    */
    printf("[RECEIVED] %s\n", inet_ntop(AF_INET, &cli.sin_addr.s_addr, ip, INET_ADDRSTRLEN));
    if (file_log_process(&recv_log) < 0) 
    {
      printf("File logging error: failed to process last log packet\n");
      return 1;
    }
  }

  return 0;
}
