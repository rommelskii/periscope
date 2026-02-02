#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#include "log.h"
#include "log_serialize.h"

#include "testing_utils.h"


/**
  * file: test_log_serialize.c
  * Contains test suite for serializing and deserializing a log
  */

int tests_failed = 0;

int main() 
{
  /** 
   * TEST PARAMETERS
   */
  uint8_t buf[2048];
  memset(buf, 0, sizeof(buf));

  uint32_t test_magic_number = htonl(MAGIC_NUMBER); //< only for counter checking
  uint32_t test_src_ip = htonl(INADDR_LOOPBACK);
  uint8_t test_src_mac[6] = {0xDE, 0xEA, 0xDD, 0xBE, 0xEE, 0xFF};
  log_type_t test_type = STANDARD;
  char* test_content = "USB detected at /dev/sdb0";

  /**
   * TEST INITIALIZATION 
   */
  log_t before = create_log(test_src_ip, test_src_mac, test_type, test_content);
  log_t after = {0};
  
  serialize_log(&before, buf, sizeof(buf));
  deserialize_log(&after, buf);

  /**
   * TEST PROPER
   */
  printf("----LOG SERIALIZATION TESTS----\n");
  EXPECT(after.src_ip == test_src_ip, "serialized source ip test");
  EXPECT(strncmp((const char*)after.src_mac, (const char*)test_src_mac, MACADDRLEN) == 0, "serialized mac test");
  EXPECT(after.type == test_type, "serialized type test");
  EXPECT(strncmp((const char*)after.content, test_content, strnlen(test_content, MAXMSGLEN+1)) == 0, "serialized content test");

  if (tests_failed > 0)
  {
    printf("%s: One or more tests have failed\n", __FILENAME__);
    return 1;
  }
}
