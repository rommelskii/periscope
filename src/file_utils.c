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
  if (plog == NULL) 
  {
    fprintf(stderr, "File processing error: input log object cannot be null\n");
    return -1;
  }

  char buf[FILE_MAXSIZE]; 
  memset(buf, 0, sizeof(buf));

  FILE* pconf = fopen(FILE_CONF_PATH, "r"); 
  if (pconf == NULL)
  {
    perror("File processing error: cannot find the configuration file");
    return -1;
  }

  if (fgets(buf, sizeof(buf), pconf) == NULL) 
  {
    fprintf(stderr, "File processing error: empty or unreadable configuration file\n");
    fclose(pconf);
    return -1;
  }
  fclose(pconf);

  buf[strcspn(buf, "\r\n")] = 0;

  FILE* plogf = fopen(buf, "a");
  if (plogf == NULL)
  {
    fprintf(stderr, "File processing error: cannot open logging path [%s]\n", buf);
    return -1;
  }

  char ip_str[INET_ADDRSTRLEN];
  const char* type_str;
  char* mac_str;

  if (inet_ntop(AF_INET, &plog->src_ip, ip_str, sizeof(ip_str)) == NULL) 
  {
    strncpy(ip_str, "unknown", sizeof(ip_str));
  }

  mac_str = log_mac_to_string(plog->src_mac); 
  type_str = log_type_to_string(plog->type);

  char line_content[FILE_MAXSIZE];

  int written = snprintf(line_content, sizeof(line_content), 
                         "src=%s mac=%s type=%s content='%s'\n", 
                         ip_str, mac_str, type_str, plog->content);

  if (written >= (int)sizeof(line_content)) 
  {
    fprintf(stderr, "File writing warning: log entry was truncated\n");
  }

  if (fputs(line_content, plogf) == EOF) 
  {
    perror("File writing error: failed to log to file");
    fclose(plogf);
    // If your mac_str was malloc'd, call free(mac_str) here!
    return -1;
  }

  fclose(plogf);

  return 0;
}
