cmake_minimum_required(VERSION 3.1)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Find OpenCV, you may need to set OpenCV_DIR variable to the absolute path to
# the directory containing OpenCVConfig.cmake file via the command line or GUI
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

project(DisplayImage)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(DisplayImage main.cpp)
target_link_libraries(DisplayImage ${OpenCV_LIBS})

function(copy_cv_runtime TARGET)
  foreach(file_i ${ARGN})
    set(source ${OpenCV_DIR}/${OpenCV_ARCH}/${OpenCV_RUNTIME}/bin/${file_i}.dll)
    message(STATUS "${source} ==> ${CMAKE_BINARY_DIR}")
    add_custom_command(TARGET DisplayImage POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_if_different ${source}
                               ${CMAKE_BINARY_DIR})
  endforeach(file_i)
endfunction()

copy_cv_runtime(opencv_core310d
                opencv_highgui310d
                opencv_imgcodecs310d
                opencv_videoio310d
                opencv_imgproc310d)
