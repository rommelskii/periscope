#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "log.h"

/**
  * file: test_log.c
  * Unit test for the log data type
  */


int main()
{
  printf("[Test] Log datatype... ");
  log_t log = {0};

  uint8_t test_mac[6] = {0xDE, 0xEA, 0xDD, 0xBE, 0xEE, 0xFF};
  uint32_t magic_number = 0xdeadbeef;
  uint32_t test_ip = inet_addr("127.0.0.1");

  log_type_t test_type = STANDARD;

  char* test_content = "USB detected at /dev/sdb0";

  log.magic_number = magic_number;
  log.src_ip = test_ip;
  memcpy(log.src_mac, test_mac, MACADDRLEN);
  log.type = test_type;
  memcpy(log.content, test_content, strlen(test_content)+1);
  
  assert(log.magic_number == magic_number);
  assert(log.src_ip == test_ip);

  for (size_t i = 0; i < MACADDRLEN; ++i) 
  {
    assert(log.src_mac[i] == test_mac[i]);
  }

  assert(log.type == test_type);

  assert(strcmp(log.content, test_content) == 0);

  printf("PASSED\n");
}

