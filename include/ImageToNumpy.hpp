#include "pybind11/numpy.h"
#include <string>

pybind11::array_t<float> openImage(std::string filename);
