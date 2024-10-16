cmake_minimum_required(VERSION 3.14)
project(liblinalg
    VERSION 1.0.0
    DESCRIPTION "C++ library for Linear Algebra"
    LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# LIBLINALG_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(LIBLINALG_BUILD_TESTS "Build liblinalg tests" OFF)
option(LIBLINALG_INSTALL "Generate target for installing liblinalg" ${is_top_level})
set_if_undefined(LIBLINALG_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/liblinalg" CACHE STRING
    "Install path for liblinalg package-related CMake files")

if(DEFINED LIBLINALG_SHARED_LIBS)
	set(BUILD_SHARED_LIBS ${LIBLINALG_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(liblinalg) # initialized below
add_library(liblinalg::liblinalg ALIAS liblinalg)

#----------------------------------------------------------------------------------------------------------------------
# lib sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(liblinalg EXPORT_FILE_NAME include/liblinalg/${export_file_name})

set(sources
    include/liblinalg/export.h
    include/liblinalg/matrix.h
    src/matrix.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# liblinalg target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(liblinalg PRIVATE ${sources})
target_compile_definitions(liblinalg PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:LIBLINALG_STATIC_DEFINE>")

target_include_directories(liblinalg
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(liblinalg PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(LIBLINALG_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/liblinalg-config.cmake.in liblinalg-config.cmake
	    INSTALL_DESTINATION "${LIBLINALG_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(liblinalg-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS liblinalg EXPORT liblinalg_export
        RUNTIME COMPONENT liblinalg
        LIBRARY COMPONENT liblinalg NAMELINK_COMPONENT liblinalg-dev
        ARCHIVE COMPONENT liblinalg-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT liblinalg-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/liblinalg/${export_file_name}"
        COMPONENT liblinalg-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/liblinalg")

    set(targets_file "liblinalg-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "liblinalg-static-targets.cmake")
    endif()

    install(EXPORT liblinalg_export
        COMPONENT liblinalg-dev
        FILE "${targets_file}"
	DESTINATION "${LIBLINALG_INSTALL_CMAKEDIR}"
        NAMESPACE liblinalg::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/liblinalg-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/liblinalg-config-version.cmake"
        COMPONENT liblinalg-dev
	DESTINATION "${LIBLINALG_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:liblinalg>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:liblinalg>/$<TARGET_FILE_PREFIX:liblinalg>$<TARGET_FILE_BASE_NAME:liblinalg>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT liblinalg-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

if(LIBLINALG_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
