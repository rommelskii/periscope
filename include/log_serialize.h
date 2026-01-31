#ifndef LOG_SERIALIZE_H_
#define LOG_SERIALIZE_H_

#include "log.h"

/**
  * @brief Serializes a log to a byte buffer
  *
  * @param plog Pointer to the log to be serialized
  * @param buf Destination byte array
  * @param maxsize Maximum length to be serialized
  *
  * @return 0 if success. -1 if failure
  */
int serialize_log(log_t* plog, uint8_t* buf, size_t maxsize);

/**
  * @brief Unpacks a byte stream to a log type
  * @param plog Destination log variable
  * @param buf Source byte array to be deserialized
  *
  * @return 0 if success. -1 if failure
  */
int deserialize_log(log_t* plog, uint8_t* buf);
#endif //LOG_SERIALIZE_H_
