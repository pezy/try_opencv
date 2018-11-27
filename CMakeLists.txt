cmake_minimum_required(VERSION 3.1)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find OpenCV, you may need to set OpenCV_DIR variable to the absolute path to
# the directory containing OpenCVConfig.cmake file via the command line or GUI
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

project(TryOpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

set(CV_DLL ${OpenCV_DIR}/${OpenCV_ARCH}/${OpenCV_RUNTIME}/bin)
file(GLOB CV_RUNTIMES ${CV_DLL}/opencv_core310d.dll
                ${CV_DLL}/opencv_highgui310d.dll
                ${CV_DLL}/opencv_imgcodecs310d.dll
                ${CV_DLL}/opencv_videoio310d.dll
                ${CV_DLL}/opencv_imgproc310d.dll)

add_custom_target(CopyRuntime)
foreach(cv_runtime ${CV_RUNTIMES})
  message(STATUS "Copy ${cv_runtime} ==> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug")
  add_custom_command(TARGET CopyRuntime PRE_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_if_different ${cv_runtime}
                               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
endforeach()

add_subdirectory(DisplayImage)
add_subdirectory(ChangeImage)

