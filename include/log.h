#ifndef LOG_H_
#define LOG_H_

/**********************************************************************
 * file: log.h
 * Contains the definition of the Periscope log type and its public API
 **********************************************************************/

/****************************************
 * Constants
 ****************************************/
#define MACADDRLEN 6


/****************************************
  * Type Definitions
 ****************************************/
typedef enum log_type 
{
  CRITICAL,
  WARNING,
  STANDARD,
} log_type_t;

typedef struct 
{
  uint32_t    src_ip;
  uint8_t     src_mac[MACADDRLEN];
  log_type_t  type; 
  char*       content;
} log_t;

/****************************************
  * Public API
 ****************************************/

/**
  * @brief Initializes a log
  * @param plog Pointer to uninitialized log variable
  */
void initialize_log (log_t* plog);

/**
  * @brief Prints a log to stdout
  * @param plog Pointer to log to be printed
  */
void print_log (const log_t* plog);

/**
  * @brief Serializes a log to a byte buffer
  *
  * @param plog Pointer to the log to be serialized
  * @param buf Destination byte array
  * @param maxsize Maximum length to be serialized
  *
  * @return 0 if success. -1 if failure
  */
int serialize_log(log_t* plog, uint8_t buf, size_t maxsize);

/**
  * @brief Unpacks a byte stream to a log type
  * @param plog Destination log variable
  * @param buf Source byte array to be deserialized
  *
  * @return 0 if success. -1 if failure
  */
int deserialize_log(log_t* plog, uint8_t buf);

#endif //LOG_H_
