cmake_minimum_required(VERSION 3.10)

set(SRC_LIST psc_server.c psc_client.c)
set(LIB_LIST log.c log_serialize.c server_utils.c file_utils.c)

add_library(periscope_core STATIC ${LIB_LIST})


foreach(SRC_FILE ${SRC_LIST})
  get_filename_component(TGT_NAME ${SRC_FILE} NAME_WE)
  add_executable(${TGT_NAME} ${SRC_FILE})
  target_link_libraries(${TGT_NAME} PRIVATE periscope_core)
endforeach()

