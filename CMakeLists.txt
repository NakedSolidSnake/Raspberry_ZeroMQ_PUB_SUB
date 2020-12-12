cmake_minimum_required(VERSION 3.7.0)

project(ZeroMQ)

set (CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_BUILD_TYPE Debug)


#build server
add_executable(server "")

target_link_libraries(server PUBLIC hardware pthread czmq)

target_sources(server
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/src/server.c
  )

target_include_directories(server 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/lib  
  )

install(TARGETS server DESTINATION bin)


#build client
add_executable(client "")

target_link_libraries(client PUBLIC czmq)

target_sources(client
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/src/client.c
  )

target_include_directories(client 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/lib  
  )

install(TARGETS client DESTINATION bin)