cmake_minimum_required(VERSION 3.7)

project(LibIMEWeb)

find_package(LibIMECore REQUIRED)
find_package(LibIMEPinyin REQUIRED)

find_package(Qt5 COMPONENTS Core Network REQUIRED)
find_package(CutelystQt5 REQUIRED)

# Auto generate moc files
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)

add_definitions(-DQT_NO_KEYWORDS)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CutelystQt5_INCLUDE_DIR}
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

file(GLOB_RECURSE TEMPLATES_SRC root/*)

add_subdirectory(src)
