#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "log.h"
#include "testing_utils.h" //< for EXPECT
 
/**
  * file: test_log.c
  * Unit test for the log data type
  */

int tests_failed = 0;

int main() 
{
  /** 
   * TEST PARAMETERS
   */
  uint32_t test_magic_number = MAGIC_NUMBER; //< only for counter checking

  uint32_t test_src_ip = htonl(INADDR_LOOPBACK);
  uint8_t test_src_mac[6] = {0xDE, 0xEA, 0xDD, 0xBE, 0xEE, 0xFF};
  log_type_t test_type = STANDARD;
  char* test_content = "USB detected at /dev/sdb0";

  /**
   * TEST INITIALIZATION 
   */
  log_t test_log = create_log(test_src_ip, test_src_mac, test_type, test_content);

  /**
   * TEST PROPER
   */
  printf("----LOG TESTS----\n");
  EXPECT(ntohl(test_log.magic_number) == test_magic_number, "magic number test");
  EXPECT(test_log.src_ip == test_src_ip, "source ip test");
  EXPECT(memcmp(test_log.src_mac, test_src_mac, MACADDRLEN) == 0, "source mac test");
  EXPECT(test_log.type == test_type, "type test");
  EXPECT(memcmp(test_log.content, test_content, strnlen(test_content, MAXMSGLEN)+1) == 0, "content test");

  if (tests_failed > 0)
  {
    printf("%s: One or more tests have failed\n", __FILE__);
    return 1;
  }
}

/*
int main()
{
  printf("[Test] Log datatype... ");
  log_t log = {0};

  uint8_t test_mac[6] = {0xDE, 0xEA, 0xDD, 0xBE, 0xEE, 0xFF};
  uint32_t magic_number = 0xdeadbeef;
  uint32_t test_ip = inet_addr("127.0.0.1");

  log_type_t test_type = STANDARD;


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
*/
