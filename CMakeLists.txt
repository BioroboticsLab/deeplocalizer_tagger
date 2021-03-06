cmake_minimum_required(VERSION 2.6)

cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0009 NEW)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(deeplocalizer_tagger)

#------------------------------------------------------------------------------
# Required CPM Setup - no need to modify - See: https://github.com/iauns/cpm
#------------------------------------------------------------------------------
set(CPM_DIR "${CMAKE_CURRENT_BINARY_DIR}/cpm_packages" CACHE TYPE STRING)
find_package(Git)
if(NOT GIT_FOUND)
  message(FATAL_ERROR "CPM requires Git.")
endif()
if (NOT EXISTS ${CPM_DIR}/CPM.cmake)
  message(STATUS "Cloning repo (https://github.com/iauns/cpm)")
  execute_process(
    COMMAND "${GIT_EXECUTABLE}" clone https://github.com/iauns/cpm ${CPM_DIR}
    RESULT_VARIABLE error_code
    OUTPUT_QUIET ERROR_QUIET)
  if(error_code)
    message(FATAL_ERROR "CPM failed to get the hash for HEAD")
  endif()
endif()
include(${CPM_DIR}/CPM.cmake)

CPM_AddModule("cpm_catch"
    GIT_REPOSITORY "https://github.com/bcachet/cpm-catch")

if(NOT DEFINED CMAKECONFIG_PATH)
    CPM_AddModule("cmakeconfig"
        GIT_REPOSITORY "https://github.com/BioroboticsLab/cmakeconfig.git"
        GIT_TAG "master")
else()
    CPM_AddModule("cmakeconfig"
        SOURCE_DIR "${CMAKECONFIG_PATH}")
endif()

CPM_AddModule("cpm_nlohmann_json"
    GIT_REPOSITORY "https://github.com/berleon/cpm_nlohmann_json.git"
)

# uncomment to generate proposals
# see issue #3
# set(USE_DEEPLOCALIZER OFF)
set(BUILD_SHARED_LIBS ON)

# set(BLAS Open CACHE STRING "Use openblas")
# set(BUILD_python OFF)
# set(BUILD_python_layer OFF)

CPM_Finish()

biorobotics_config()
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})

# project dependecies
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost COMPONENTS system filesystem serialization program_options REQUIRED)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
add_definitions(${Qt5Widgets_DEFINITIONS})


include_directories(
    SYSTEM ${CATCH_INCLUDE_DIR}
    SYSTEM ${Qt5Widgets_INCLUDE_DIRS}
    SYSTEM ${OpenCV_INCLUDE_DIRS}
    SYSTEM ${Qt5OpenGL_INCLUDE_DIRS}
    SYSTEM ${Boost_INCLUDE_DIR}
)

set(libs
    ${OpenCV_LIBS}
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    Qt5::Core
    Qt5::Widgets
    Qt5::OpenGL
    ${OPENGL_LIBRARIES}
    ${CPM_LIBRARIES}
)

add_subdirectory(source/tagger)
set(test-libs ${libs} deeplocalizer-tagger)

enable_testing(true)

add_subdirectory(test)
