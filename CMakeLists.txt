cmake_minimum_required(VERSION 3.5)

set(NAME1 sequence_qImgProjGUIRef)
project(${NAME1} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(OpenCV_DIR "D:\\win10\\opencv411\\opencv\\build\\x64\\vc16\\lib")
                                   #    D:\\win10\\opencv411\\opencv\\build
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


subdirs(
    piece1_CalcHomoRevrese/src
    piece2_QtMouseMoveViewTranlated/src
    piece3_QWidgetViewMove/src
    piece4_QWidgetViewResize/src
    proj_app1_qUsbWedCamShot/src
    proj_app2_qUsbWebCamVideo/src
    )
