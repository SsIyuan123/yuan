cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

# 指定源文件目录
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}")

# 列出所有源文件
file(GLOB SOURCES
    "${SOURCE_DIR}/*.cpp"
)

# 添加可执行文件
add_executable(MyExecutable ${SOURCES})

