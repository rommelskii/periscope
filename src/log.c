#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "log.h"

void print_log (const log_t* plog) 
{
  char buf[INET_ADDRSTRLEN];
  memset(buf, 0, sizeof(buf));

  printf("IP: %s", inet_ntop(AF_INET, &(plog->src_ip), buf, INET_ADDRSTRLEN));
  printf("\n");

  printf("MAC: ");
  for (size_t i = 0; i<sizeof(plog->src_mac); ++i) 
  {
    printf("%x", plog->src_mac[i] & 0xFF);
  }
  printf("\n");

  printf("Type: ");
  switch(plog->type) 
  {
    case (CRITICAL): printf("CRITICAL"); break;
    case (WARNING): printf("WARNING"); break;
    case (STANDARD): printf("STANDARD"); break;
    default: printf("UNKNOWN"); break;
  }
  printf("\n");
  printf("Content: %s", plog->content);
  printf("\n");
  return;
}

log_t create_log(uint32_t src_ip, uint8_t* src_mac, log_type_t type, char* content)
{
  if (src_ip == htonl(INADDR_NONE)) 
  {
    printf("Log warning: src ip is possibly incorrect\n");
  }
  if ( strnlen(content, MAXMSGLEN) == 0 ) 
  {
    printf("Log warning: empty content payload received\n");
  }

  log_t log = {0};

  log.magic_number = htonl(MAGIC_NUMBER);
  log.src_ip = src_ip;
  log.type = type;
  memcpy(log.src_mac, src_mac, sizeof(log.src_mac));
  memcpy(log.content, content, strlen(content)+1);

  return log;
}
