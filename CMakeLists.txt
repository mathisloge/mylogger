cmake_minimum_required(VERSION 3.21)
project(mylogger LANGUAGES CXX VERSION 1.0.0)
include(CTest)
include(GenerateExportHeader)
include(GNUInstallDirs)

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


install(DIRECTORY include/ TYPE INCLUDE)

install(TARGETS mylogger
    EXPORT myloggerTargets
)

install(EXPORT myloggerTargets 
    FILE myloggerTargets.cmake
    DESTINATION lib/cmake/mylogger
)

include(CMakePackageConfigHelpers)
configure_package_config_file("myloggerConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/myloggerConfig.cmake"
    INSTALL_DESTINATION "lib/cmake/mylogger"
)
write_basic_package_version_file(
    myloggerConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(EXPORT myloggerTargets
    FILE myloggerTargets.cmake
    NAMESPACE mylogger::
    DESTINATION lib/cmake/mylogger
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/myloggerConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/myloggerConfigVersion.cmake"
    DESTINATION lib/cmake/mylogger
)
