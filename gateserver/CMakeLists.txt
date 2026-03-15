cmake_minimum_required(VERSION 3.10)
project(GateServer)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "src/*.cpp")

# GateServer主程序
list(REMOVE_ITEM SOURCES "${PROJECT_SOURCE_DIR}/src/testjson.cpp")

add_executable(GateServer ${SOURCES})

target_include_directories(GateServer PRIVATE 
  ${PROJECT_SOURCE_DIR}/thirdparty/boost/boost
  ${PROJECT_SOURCE_DIR}/thirdparty/boost
  ${PROJECT_SOURCE_DIR}/inc
)

target_link_directories(GateServer PRIVATE 
${PROJECT_SOURCE_DIR}/thirdparty/boost/stage/lib
${PROJECT_SOURCE_DIR}/thirdparty/jsoncpp/lib
)

target_link_libraries(GateServer
    boost_filesystem-mgw14-mt-x64-1_84
    boost_system-mgw14-mt-x64-1_84
)


# Json库测试
add_executable(TestJson "${PROJECT_SOURCE_DIR}/src/testjson.cpp")

target_include_directories(TestJson PRIVATE
  ${PROJECT_SOURCE_DIR}/thirdparty/jsoncpp/include
)

target_link_directories(TestJson PRIVATE ${PROJECT_SOURCE_DIR}/thirdparty/jsoncpp/lib)

target_link_libraries(TestJson
    jsoncpp_static
)
