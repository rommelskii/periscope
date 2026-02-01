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

/**
 * GLOBAL VARIABLES
 */
int tests_failed = 0; //< necessary for testing library

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
    printf("%s: One or more tests have failed\n", __FILENAME__);
    return 1;
  }
}
