#pragma once
#include <string>

#ifndef Q_MOC_RUN
#    pragma push_macro("Q_FOREACH")
#    pragma push_macro("foreach")
#    pragma push_macro("slots")
#    undef Q_FOREACH
#    undef foreach
#    undef slots
#    include "pybind11/embed.h"
#    include "pybind11/eval.h"
#    include "pybind11/numpy.h"
#    pragma pop_macro("Q_FOREACH")
#    pragma pop_macro("foreach")
#    pragma pop_macro("slots")
#endif

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
