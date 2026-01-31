set(TEST_SRC_LIST test_log.c test_log_serialize.c test_server.c)

foreach(SRC_FILE ${TEST_SRC_LIST})
  get_filename_component(TGT_NAME ${SRC_FILE} NAME_WE)
  add_executable(${TGT_NAME} ${SRC_FILE})
  target_link_libraries(${TGT_NAME} PRIVATE periscope_core)
endforeach()
