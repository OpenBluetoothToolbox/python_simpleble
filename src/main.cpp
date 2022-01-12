#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "simpleble/Adapter.h"

namespace py = pybind11;

#include <iostream>

class PyPeripheral : public SimpleBLE::Peripheral {
  public:
    std::map<uint16_t, SimpleBLE::ByteArray> py_manufacturer_data() {
        std::cout << "Here!" << std::endl;
        return manufacturer_data();
    }
};

PYBIND11_MODULE(simplepyble, m) {
    m.attr("__version__") = "0.0.1";

    py::class_<SimpleBLE::BluetoothService>(m, "BluetoothService")
        .def_readonly("uuid", &SimpleBLE::BluetoothService::uuid)
        .def_readonly("characteristics", &SimpleBLE::BluetoothService::characteristics);

    // TODO: Add __str__ and __repr__ methods to Peripheral class
    py::class_<SimpleBLE::Peripheral>(m, "Peripheral")
        .def("identifier", &SimpleBLE::Peripheral::identifier)
        .def("address", &SimpleBLE::Peripheral::address)
        .def("connect", &SimpleBLE::Peripheral::connect)
        .def("disconnect", &SimpleBLE::Peripheral::disconnect)
        .def("is_connected", &SimpleBLE::Peripheral::is_connected)
        .def("is_connectable", &SimpleBLE::Peripheral::is_connectable)
        .def("services", &SimpleBLE::Peripheral::services)
        .def("manufacturer_data", [](SimpleBLE::Peripheral& p) {
            std::map<uint16_t, py::bytes> ret;
            for (auto& kv : p.manufacturer_data()) {
                ret[kv.first] = py::bytes(kv.second);
            }
            return ret;
        });

    // TODO: Add __str__ and __repr__ methods to Adapter class
    py::class_<SimpleBLE::Adapter>(m, "Adapter")
        .def("get_adapters", &SimpleBLE::Adapter::get_adapters)
        .def("identifier", &SimpleBLE::Adapter::identifier)
        .def("address", &SimpleBLE::Adapter::address)
        .def("scan_start", &SimpleBLE::Adapter::scan_start)
        .def("scan_stop", &SimpleBLE::Adapter::scan_stop)
        .def("scan_is_active", &SimpleBLE::Adapter::scan_is_active)
        .def("scan_for", &SimpleBLE::Adapter::scan_for, py::call_guard<py::gil_scoped_release>())
        .def("scan_get_results", &SimpleBLE::Adapter::scan_get_results)
        .def("set_callback_on_scan_start", &SimpleBLE::Adapter::set_callback_on_scan_start)
        .def("set_callback_on_scan_stop", &SimpleBLE::Adapter::set_callback_on_scan_stop)
        .def("set_callback_on_scan_found", &SimpleBLE::Adapter::set_callback_on_scan_found)
        .def("set_callback_on_scan_updated", &SimpleBLE::Adapter::set_callback_on_scan_updated);
}
