/******************************************************
 * (C) Rommel Ronduen (rommel.ronduen2244@gmail.com)
 *
 * file: psc_client.c
 * Performs a client request to a Periscope server
******************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "log.h"
#include "log_serialize.h"
#include "server_utils.h"

#define CLI_MSG_USG "Usage: ./psc_client (logging ip) (logging level) (content)\n"

int main(int argc, char** argv)
{
  /**
  * Usage: ./psc_client (logging ip) (logging level) (content) 
  */ 

  if (argc != 4) 
  {
    fprintf(stderr, "argument error: incorrect arguments\n");
    printf(CLI_MSG_USG);
    return 1;
  }

  //cli_arg_proc(argv[1], argv[2], argv[3]);


  // Replace these with actual information
  uint32_t src_ip = inet_addr("49.49.49.2");
  uint8_t src_mac[6] = {0x32, 0x48, 0xde, 0xf6, 0xb8, 0x9e};
  log_type_t type = STANDARD;
  char* content = "[dns] received dns=S1 from mels@tsukoyomi.local";

  int sockfd;
  uint8_t buf[2048];
  struct sockaddr_in targ;
  socklen_t addrlen = sizeof(targ);

  memset(buf, 0, sizeof(buf));

  log_t sendto_log = create_log(src_ip, src_mac, type, content);
  serialize_log(&sendto_log, buf, sizeof(buf));

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  targ.sin_family = AF_INET;
  targ.sin_port = htons(PSC_PORT);
  targ.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&targ, sizeof(targ));

  return 0;
}
