cmake_minimum_required(VERSION 3.10)

project(HDR_Imaging_Cpp)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(include ${OpenCV_INCLUDE_DIRS})

add_executable(hdr
    src/main.cpp
    src/hdr_merge.cpp
    src/tonemap.cpp
)

target_link_libraries(hdr ${OpenCV_LIBS})
