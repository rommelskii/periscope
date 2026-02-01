#ifndef LOG_SERIALIZE_H_
#define LOG_SERIALIZE_H_

#include "log.h"
#include <stdint.h>

/**
  * @brief Serializes a log to a byte buffer
  *
  * @param plog Pointer to the log to be serialized
  * @param buf Destination byte array
  * @param maxsize Maximum length to be serialized
  */
void serialize_log(log_t* plog, uint8_t* buf, size_t maxsize);

/**
  * @brief Unpacks a byte stream to a log type
  * @param plog Destination log variable
  * @param buf Source byte array to be deserialized
  */
void deserialize_log(log_t* plog, uint8_t* buf);

#endif //LOG_SERIALIZE_H_
