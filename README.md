# import_dicom_cpp

This is just a light [pybind11](https://github.com/pybind/pybind11) wrapper around pydicom (https://pydicom.github.io/) launching a Python interpreter to use the capabilities of pydicom to open DICOMs in C++ applications.

It needs to be built with a Python interpreter with pydicom installed.

# Usage 

This is a header-only library.
See [test](test) for a usage example.
If you only use [`ImageToNumpy.hpp`](include/ImageToNumpy.hpp) no external dependencies apart from a Python interpreter are needed.
[`NumpyToOpenVdb.hpp`](include/NumpyToOpenVdb.hpp) requires [OpenVDB](https://github.com/AcademySoftwareFoundation/openvdb) (`libopenvdb-dev` on Ubuntu).
