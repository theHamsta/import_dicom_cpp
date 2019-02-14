/*
 * ImageToNumpy.cpp
 * Copyright (C) 2019 seitz_local <seitz_local@lmeXX>
 *
 * Distributed under terms of the GPLv3 license.
 */

#include "ImageToNumpy.hpp"

#include "pybind11/eval.h"

namespace py = pybind11;
using namespace pybind11::literals;


pybind11::array_t< float > openImage(std::string filename)
{
    auto locals      = py::dict("filename"_a = filename);

    py::exec(R"(
from os.path import dirname, isdir
from dsareco.file_conversion import dicomdir2vol

dicom_dir = filename if isdir(filename) else dirname(filename)
vol, spacing = dicomdir2vol(dicom_dir)
				 )",
             py::globals(), locals);
    py::array_t< float > vol = py::eval("vol", py::globals(), locals);
    return vol;
}
