#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "simpleble/Adapter.h"

namespace py = pybind11;

PYBIND11_MODULE(simplepyble, m) {
    m.attr("__version__") = "0.0.1";

    // TODO: Add __str__ and __repr__ methods to Adapter class
    py::class_<SimpleBLE::Adapter>(m, "Adapter")
        .def("get_adapters", &SimpleBLE::Adapter::get_adapters)
        .def("identifier", &SimpleBLE::Adapter::identifier)
        .def("address", &SimpleBLE::Adapter::address);
}
