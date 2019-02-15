#include "pybind11/numpy.h"
#include "pybind11/embed.h"
#include <string>

pybind11::array_t<float> openImage(const std::string& filename);
