cmake_minimum_required(VERSION 3.0)
project(main)
#  配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
#  配置头文件搜索路径
#  include_directories()
#  配置库文件搜索路径
#  link_directories()
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(SRC_LIST ./muduo_server.cpp)
add_executable(server ${SRC_LIST} )

target_link_libraries(server muduo_net muduo_base pthread)
