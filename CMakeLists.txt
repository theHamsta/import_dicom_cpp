cmake_minimum_required(VERSION 3.5)

project(import_dicom_cpp)

add_subdirectory(pybind11)

if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

set(CXX_STANDARD 17)
set(OPENVDB_LIBRARIES
    tbb
    openvdb
    Half
    IexMath
    Iex
    IlmThread
    Imath)

aux_source_directory(source SOURCES)

add_library(import_dicom_cpp INTERFACE)

target_include_directories(import_dicom_cpp
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    )

target_link_libraries(
    import_dicom_cpp
    INTERFACE
    pybind11::embed
    ${OPENVDB_LIBRARIES}
    )

add_subdirectory(test)
