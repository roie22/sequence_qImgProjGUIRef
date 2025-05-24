cmake_minimum_required(VERSION 3.5)

set(NAME1 sequence_related)
project(${NAME1} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    find_package(OpenCV REQUIRED PATHS "D:\\win10\\opencv411\\opencv\\build")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    find_package(OpenCV REQUIRED)
else()
endif()

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_DIR})


##################################################
include(cmake_Kelvin/myprojectsetting.cmake)
##################################################


subdirs(CalcHomoRevrese/src
    proj_qUsbWedCamShot/src
    proj_qUsbWebCamVideo/src
    QtMouseMoveViewTranlated/src
    QWidgetViewMove/src
    QWidgetViewResize/src
    )
