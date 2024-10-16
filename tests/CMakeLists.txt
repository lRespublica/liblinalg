cmake_minimum_required(VERSION 3.14)
project(liblinalg-tests)


#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include("../cmake/utils.cmake")
include(GoogleTest)
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

if(is_top_level)
    enable_testing()
endif()


#----------------------------------------------------------------------------------------------------------------------
# tests dependencies
#----------------------------------------------------------------------------------------------------------------------

if(is_top_level)
    find_package(liblinalg REQUIRED)
endif()

find_package(GTest CONFIG REQUIRED)

#----------------------------------------------------------------------------------------------------------------------
# tests sources
#----------------------------------------------------------------------------------------------------------------------

set(sources
    basic_tests.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# tests target
#----------------------------------------------------------------------------------------------------------------------

add_executable(liblinalg-tests)
target_sources(liblinalg-tests PRIVATE ${sources})

target_link_libraries(liblinalg-tests
    PRIVATE
        liblinalg::liblinalg
        GTest::gtest_main)

if(NOT is_top_level)
    win_copy_deps_to_target_dir(liblinalg-tests liblinalg::liblinalg)
endif()

include(GoogleTest)
gtest_discover_tests(liblinalg-tests)
