#ifndef LOG_H_
#define LOG_H_

/**********************************************************************
 * file: log.h
 * Contains the definition of the Periscope log type and its public API
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>

/****************************************
 * Constants
 ****************************************/
#define MACADDRLEN 6
#define MAXMSGLEN 256 
#define MAGIC_NUMBER 0xDEADB33F


/****************************************
  * Type Definitions
 ****************************************/
typedef enum log_type 
{
  CRITICAL,
  WARNING,
  STANDARD,
} log_type_t;


#pragma pack(push, 1)
typedef struct 
{
  uint32_t    magic_number;
  uint32_t    src_ip;
  uint8_t     src_mac[MACADDRLEN];
  log_type_t  type; 
  char        content[MAXMSGLEN];
} log_t;
#pragma pack(pop)

/****************************************
  * Public API
 ****************************************/

/**
  * @brief Prints a log to stdout
  * @param plog Pointer to log to be printed
  */
void print_log (const log_t* plog);

/**
  * @brief Initializes a log
  * @param src_ip Source IP in network order
  * @param src_mac Source MAC address byte array
  * @param type Log type enum
  * @param content Log content string 
  */
log_t create_log(uint32_t src_ip, uint8_t* src_mac, log_type_t type, char* content);

#endif //LOG_H_
