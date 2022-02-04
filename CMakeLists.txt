cmake_minimum_required(VERSION 3.21)
project(mylogger LANGUAGES CXX)
include(CTest)
include(GenerateExportHeader)

find_package(spdlog CONFIG REQUIRED)


set(shared_output_dir "${CMAKE_CURRENT_BINARY_DIR}/out")

add_library(mylogger src/context.cpp)
add_library(mylogger::mylogger ALIAS mylogger)
set_target_properties(mylogger PROPERTIES 
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY "${shared_output_dir}"
)
target_link_libraries(mylogger PUBLIC spdlog::spdlog)
target_include_directories(mylogger PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
)
generate_export_header(mylogger)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
