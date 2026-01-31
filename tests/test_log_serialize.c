#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#include "log.h"
#include "log_serialize.h"


/**
  * file: test_log_serialize.c
  * Contains test suite for serializing and deserializing a log
  */

int main()
{
  uint8_t buf[2048]; 
  memset(buf, 0, sizeof(buf));

  uint32_t src_ip = inet_addr("49.2.0.4");
  uint8_t src_mac[6] = {0xde, 0xad, 0xbe, 0xef, 0x69, 0x69};
  log_type_t type = CRITICAL;
  char* content = "[server] working from localhost:30";

  log_t before = create_log(src_ip, src_mac, type, content);
  serialize_log(&before, buf, sizeof(buf));
  
  log_t after = {0}; 
  deserialize_log(&after, buf);


  assert(after.src_ip == src_ip);
  for (size_t i=0; i<MACADDRLEN; ++i)
  {
    assert(after.src_mac[i] == src_mac[i]);
  }

  assert(after.type == type);
  assert(strncmp(after.content, content, MAXMSGLEN) == 0);

  printf("[Test] Serialization process... PASSED\n");
}



