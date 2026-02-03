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

#define CLI_MSG_USG "Usage: ./psc_client (logging ip) (logging type) (content)\n"
#define CLI_ARG_MAXSIZE 512

void cli_arg_proc(char* ip, char* type, char* content, char** argv);

int main(int argc, char** argv)
{
  /**
  * Usage: ./psc_client (logging ip) (logging type) (content) 
  */ 

  if (argc != 4) 
  {
    fprintf(stderr, "argument error: incorrect arguments\n");
    printf(CLI_MSG_USG);
    return 1;
  }


  char arg_ip[INET_ADDRSTRLEN+1];
  char arg_type[MAXTYPELEN+1];
  char arg_content[CLI_ARG_MAXSIZE];

  cli_arg_proc(arg_ip, arg_type, arg_content, argv);

  // Replace these with actual information
  uint32_t src_ip = inet_addr(arg_ip);
  uint8_t src_mac[6] = {0x32, 0x48, 0xde, 0xf6, 0xb8, 0x9e};
  log_type_t type = string_to_log_type(arg_type); 
  char* content = arg_content;

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

void cli_arg_proc(char* ip, char* type, char* content, char** argv)
{
  memset(ip, 0, sizeof(ip));
  memset(type, 0, sizeof(type));
  memset(content, 0, sizeof(content));
  memcpy(ip, argv[1], INET_ADDRSTRLEN+1);
  memcpy(type, argv[2], MAXTYPELEN+1);
  memcpy(content, argv[3], CLI_ARG_MAXSIZE);
  return;
}
