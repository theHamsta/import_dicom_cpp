cmake_minimum_required (VERSION 3.5)

add_executable(test_import_dicom
    test_import_dicom.cpp
    )

target_link_libraries(
    test_import_dicom
    PRIVATE
    import_dicom_cpp
    )
