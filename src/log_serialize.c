/******************************************************
 * (C) Rommel Ronduen (rommel.ronduen2244@gmail.com)
 *
 * file: log_serialize.c
 * Contains the implementations of the serialization methods
******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

#include "log.h"
#include "log_serialize.h"

void serialize_log(log_t* plog, uint8_t* buf, size_t maxsize) 
{
  memset(buf, 0, maxsize);
  memcpy(buf, plog, sizeof(log_t));
  return;
}

/**
  * @note This function does not validate the MAC address.
  */
int deserialize_log(log_t* plog, uint8_t* buf) 
{
  //Check first if magic number can be found
  uint32_t temp_magic_number = (uint32_t)buf[0] << 24 | (uint32_t)buf[1] << 16 | (uint32_t)buf[2] << 8 | (uint32_t)buf[3];
  if (temp_magic_number != MAGIC_NUMBER) 
  {
    printf("Deserialization error: malformed log (incorrect magic cookie)\n");
    return -1;
  }

  //Validate IP
  uint32_t temp_ip = (uint32_t)buf[7] << 24 | (uint32_t)buf[6] << 16 | (uint32_t)buf[5] << 8 | (uint32_t)buf[4];
  if(temp_ip == INADDR_NONE) 
  {
    printf("Deserialization error: invalid IP\n");
    return -1;
  }

  //Validate type
  log_type_t temp_type = (log_type_t)buf[8 + MACADDRLEN]; // 8 = magic num len + ip len
  if (temp_type == UNKNOWN) 
  {
    printf("Deserialization error: unknown log type\n");
    return -1;
  }

  //Validate content 
  char temp_content[MAXMSGLEN];
  memset(temp_content, 0, sizeof(temp_content));
  memcpy(temp_content, &buf[8+MACADDRLEN+sizeof(log_type_t)], MAXMSGLEN);

  //Validate time
  //time_t temp = (uint64_t)buf[8+MACADDRLEN+sizeof(log_type_t) + 1] << 56 | 
  time_t temp_time = 0;
  for (size_t i=0; i<8; ++i)
  {
    temp_time |= (uint64_t)buf[8+MACADDRLEN+sizeof(log_type_t) + MAXMSGLEN + i ] << (i * 8);
  }

  if (temp_time == 0) 
  {
    printf("Deserialization error: time is unset\n");
    return -1;
  }

  if (strnlen(temp_content, MAXMSGLEN) == 0) 
  {
    printf("Deserialization error: empty content field\n");
    return -1; 
  }

  // Finally, set the plog attributes to validated values
  plog->magic_number = temp_magic_number;
  plog->src_ip = temp_ip;
  plog->type = temp_type;
  memcpy(plog->src_mac, &buf[8], MACADDRLEN);
  memcpy(plog->content, &buf[8 + MACADDRLEN + sizeof(log_type_t)], MAXMSGLEN);
  plog->event_time = temp_time;

  return 0;
}
