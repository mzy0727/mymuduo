cmake_minimum_required(VERSION 3.10)
project(learn_muduo)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 设置库文件输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 添加头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
# src包含框架所以源代码
add_subdirectory(src)
