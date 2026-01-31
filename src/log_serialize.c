#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "log_serialize.h"

void serialize_log(log_t* plog, uint8_t* buf, size_t maxsize) 
{
  memset(buf, 0, maxsize);
  memcpy(buf, plog, sizeof(log_t));
  return;
}

void deserialize_log(log_t* plog, uint8_t* buf) 
{
  plog->magic_number = (uint32_t)buf[0] << 24 | (uint32_t)buf[1] << 16 | (uint32_t)buf[2] << 8 | (uint32_t)buf[3];
  plog->src_ip = (uint32_t)buf[7] << 24 | (uint32_t)buf[6] << 16 | (uint32_t)buf[5] << 8 | (uint32_t)buf[4];

  memcpy(plog->src_mac, &buf[8], MACADDRLEN);

  uint8_t temp_type = buf[8 + MACADDRLEN]; // 8 = magic num len + ip len
  plog->type = (log_type_t)temp_type;

  memcpy(plog->content, &buf[8 + MACADDRLEN + sizeof(log_type_t)], MAXMSGLEN);

  return;
}
