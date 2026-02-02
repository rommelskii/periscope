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
  char* actual_mac = "de:ab:cd:ef:fe:ee";
  char* actual_type = "CRITICAL";

  /**
   * TEST INITIALIZATION 
   */
  uint8_t test_mac[6] = {0xDE, 0xAB, 0xCD, 0xEF, 0xFE, 0xEE};
  log_type_t test_type = CRITICAL;

  char* result_mac = log_mac_to_string(test_mac);
  char* result_type = log_type_to_string(test_type);

  /**
   * TEST PROPER
   */
  
  printf("----LOG FORMATTER TESTS----\n");
  EXPECT(strncmp(result_mac, actual_mac, MACADDRLEN) == 0, "MAC formatter test");
  EXPECT(strcmp(result_type, actual_type) == 0, "Log type formatter test");

  if (tests_failed > 0)
  {
    printf("%s: One or more tests have failed\n", __FILENAME__);
    return 1;
  }
}

