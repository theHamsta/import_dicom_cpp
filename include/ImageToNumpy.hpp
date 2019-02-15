#pragma once
#include <string>

#include "pybind11/embed.h"
#include "pybind11/eval.h"
#include "pybind11/numpy.h"

template< typename T >
inline pybind11::array_t< T > imageToNumpy(const std::string& filename)
{
    namespace py = pybind11;
    using namespace pybind11::literals;
    auto locals = py::dict("filename"_a = filename);

    py::exec(R"(
from os.path import dirname, isdir
from dsareco.file_conversion import dicomdir2vol

dicom_dir = filename if isdir(filename) else dirname(filename)
vol, spacing = dicomdir2vol(dicom_dir)
				 )",
             py::globals(), locals);
    py::array_t< T > vol = py::eval("vol", py::globals(), locals);
    return vol;
}
