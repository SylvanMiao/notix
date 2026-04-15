cmake_minimum_required(VERSION 3.10)
project(notix_httpserver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Threads REQUIRED)

find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(JSONCPP QUIET jsoncpp)
endif()

if(NOT JSONCPP_FOUND)
    find_path(JSONCPP_INCLUDE_DIR
        NAMES json/json.h jsoncpp/json/json.h
        PATH_SUFFIXES jsoncpp
    )
    find_library(JSONCPP_LIBRARY NAMES jsoncpp)

    if(NOT JSONCPP_LIBRARY)
        message(FATAL_ERROR "jsoncpp library not found. Please install libjsoncpp-dev.")
    endif()

    set(JSONCPP_INCLUDE_DIRS ${JSONCPP_INCLUDE_DIR})
    set(JSONCPP_LIBRARIES ${JSONCPP_LIBRARY})
endif()

file(GLOB_RECURSE HTTPSERVER_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

if(NOT HTTPSERVER_SOURCES)
    message(FATAL_ERROR "No source files found under ${CMAKE_CURRENT_SOURCE_DIR}/src")
endif()

add_executable(http_server ${HTTPSERVER_SOURCES})

target_include_directories(http_server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/http
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/router
    ${JSONCPP_INCLUDE_DIRS}
)

target_link_libraries(http_server PRIVATE
    Boost::system
    Threads::Threads
    ${JSONCPP_LIBRARIES}
)

# 运行目录位于 build 时，自动复制静态资源
add_custom_command(TARGET http_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:http_server>/static"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/static"
            "$<TARGET_FILE_DIR:http_server>/static"
    COMMENT "Copy static resources"
)

message(STATUS "Project source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Sources: ${HTTPSERVER_SOURCES}")
