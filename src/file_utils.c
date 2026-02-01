#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>

#include "log.h"
#include "file_utils.h"

//TODO: make this cleaner by using subroutines

int file_log_process(log_t* plog) 
{
  /**
  * Configuration loading and log stream handling
  */
  if (plog == NULL) 
  {
    printf("File processing error: input log object cannot be null\n");
    return -1;
  }

  char buf[FILE_MAXSIZE]; 
  memset(buf, 0, sizeof(buf));

  FILE* pconf = fopen(FILE_CONF_PATH, "r"); 
  if (pconf == NULL)
  {
    printf("File processing error: cannot find the configuration file\n");
    return -1;
  }

  fgets(buf, sizeof(buf), pconf);
  if (strnlen(buf, FILE_MAXSIZE) == 0) 
  {
    printf("File processing error: empty configuration file\n");
    return -1;
  }

  fclose(pconf); 

  FILE* plogf = fopen(buf, "a"); //< buffer should contain the config content (path)
  if (plogf == NULL)
  {
    printf("File processing error: cannot open logging path specified in configuration file\n");
    return -1;
  }

  /**
    * Begin stream input
    */

  char* ip;
  char* mac;
  char* type;
  char* content;

  inet_ntop(AF_INET, &plog->src_ip, ip, INET_ADDRSTRLEN);
  mac = log_mac_to_string(plog->src_mac); 
  type = log_type_to_string(plog->type);
  memcpy(content, plog->content, MAXMSGLEN); 

  char line_content[FILE_MAXSIZE];
  snprintf(line_content, sizeof(line_content), "src=%s mac=%s type=%s content='%s'", ip, mac, type, content);

  if (fputs(line_content, plogf) < 0) 
  {
    printf("File writing error: failed to log\n");
  }

  fclose(plogf);

  return 0;
}
