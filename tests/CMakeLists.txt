message(STATUS "BUILD TESTS")

add_executable(integration-test main.cpp)
target_link_libraries(integration-test PRIVATE 
    mylogger::mylogger
)

set_target_properties(integration-test PROPERTIES 
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY "${shared_output_dir}"
)
