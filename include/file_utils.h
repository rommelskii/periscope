#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include <stdlib.h>
#include <stdio.h>

#include <log.h>


/**
  * @brief Encodes log information to a file defined by the path in the configuration
  * @param plog Pointer to log object to be file-encoded
  */
int file_log_process(log_t* plog);

#endif //FILE_UTILS_H_
