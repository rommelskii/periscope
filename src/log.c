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
