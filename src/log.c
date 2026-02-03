
/******************************************************
 * (C) Rommel Ronduen (rommel.ronduen2244@gmail.com)
 *
 * file: log.c
 * Contains log data type and method implementations
******************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "log.h"

void print_log (const log_t* plog) 
{
  if (plog->magic_number != MAGIC_NUMBER)
  {
    printf("Log print error: malformed log (invalid magic number)\n");
    return;
  }
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
  memcpy(log.src_mac, src_mac, MACADDRLEN);
  memcpy(log.content, content, strlen(content)+1);

  return log;
}
 
char* log_mac_to_string(uint8_t* pmac) 
{
  static char buf[18]; 
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x", 
           pmac[0], pmac[1], pmac[2], pmac[3], pmac[4], pmac[5]);
  return buf;
}

char* log_type_to_string(log_type_t type) 
{
  switch(type)
  {
    case (CRITICAL): return "CRITICAL"; break;
    case (WARNING): return "WARNING"; break;
    case (STANDARD): return "STANDARD"; break;
    case (UNKNOWN): return "UNKNOWN"; break;
    default: return NULL; break;
  }
}

log_type_t string_to_log_type(const char* s_type)
{
  if (s_type == NULL || strnlen(s_type, ) == 0) 
  {
    fprintf(stderr, "string_to_log_type error: s_type cannot be null or empty\n");
    return UNKNOWN;
  }

  int is_critical = strncmp("CRITICAL", s_type, MAXTYPELEN);
  int is_standard = strncmp("STANDARD", s_type, MAXTYPELEN);
  int is_warning = strncmp("WARNING", s_type, MAXTYPELEN);

  if (is_critical == 0)
  {
    return CRITICAL; 
  }
  if (is_standard == 0)
  {
    return STANDARD; 
  }
  if (is_warning == 0)
  {
    return WARNING; 
  }

  return UNKNOWN;
}
