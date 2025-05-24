cmake_minimum_required(VERSION 3.5)

set(NAME piece1_CalcHomoRevrese)
project(${NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#if(CMAKE_SYSTEM_NAME MATCHES "Windows")
#    find_package(OpenCV REQUIRED PATHS "D:\\win10\\opencv411\\opencv\\build")
#elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
#    find_package(OpenCV REQUIRED)
#else()
#endif()

#include_directories(${OpenCV_INCLUDE_DIRS})
#link_directories(${OpenCV_DIR})

##################################################
#include(cmake_Kelvin/myprojectsetting.cmake)
##################################################

file(GLOB allsourceheaders ./*.cpp ./*.h ./*.hpp ./*.ui ./*.qrc)

add_executable(${NAME} main.cpp ${allsourceheaders})
target_link_libraries(${NAME} PRIVATE ${OpenCV_LIBS})
#target_link_libraries(${NAME} ${OpenCV_LIBS})

