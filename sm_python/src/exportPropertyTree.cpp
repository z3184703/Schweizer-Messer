#include <numpy_eigen/boost_python_headers.hpp>
#include <sm/BoostPropertyTree.hpp>

double getDouble(const sm::PropertyTree * p, const std::string & key) {
  return p->getDouble(key);
}

double getDoubleDefault(sm::PropertyTree * p, const std::string & key, double defaultValue) {
  return p->getDouble(key, defaultValue);
}

int getInt(const sm::PropertyTree * p, const std::string & key) {
  return p->getInt(key);
}

int getIntDefault(sm::PropertyTree * p, const std::string & key, int defaultValue) {
  return p->getInt(key, defaultValue);
}

bool getBool(const sm::PropertyTree * p, const std::string & key) {
  return p->getBool(key);
}

bool getBoolDefault(sm::PropertyTree * p, const std::string & key, bool defaultValue) {
  return p->getBool(key, defaultValue);
}

std::string getString(const sm::PropertyTree * p, const std::string & key) {
  return p->getString(key);
}

std::string getStringDefault(sm::PropertyTree * p, const std::string & key, const std::string & defaultValue) {
  return p->getString(key, defaultValue);
}

void exportPropertyTree() {
  using namespace boost::python;
  using namespace sm;

  class_<PropertyTree>("PropertyTree", init<const PropertyTree &, const std::string &>("PropertyTree(PropertyTree parent, string childNamespace)"))
      .def("getInt", &getInt).def("getIntDefault", &getIntDefault)
      .def("getString", &getString)
      .def("getStringDefault", &getStringDefault)
      .def("getBool", &getBool).def("getBoolDefault", &getBoolDefault)
      .def("getDouble", &getDouble).def("getDoubleDefault", &getDoubleDefault)
      .def("doesKeyExist", &PropertyTree::doesKeyExist);

  class_<MutablePropertyTree, bases<PropertyTree>>("MutablePropertyTree", init<const MutablePropertyTree &, const std::string &>("MutablePropertyTree(MutablePropertyTree parent, string childNamespace)"))
      .def("getOrCreateInt", static_cast<int(MutablePropertyTree::*)(const std::string &, int)>(&MutablePropertyTree::getInt))
      .def("getOrCreateString", static_cast<std::string(MutablePropertyTree::*)(const std::string &, const std::string&)>(&MutablePropertyTree::getString))
      .def("getOrCreatetBool", static_cast<bool(MutablePropertyTree::*)(const std::string &, bool)>(&MutablePropertyTree::getBool))
      .def("getOrCreateDouble", static_cast<double(MutablePropertyTree::*)(const std::string &, double)>(&MutablePropertyTree::getDouble))
      .def("setInt", &MutablePropertyTree::setInt)
      .def("setBool", &MutablePropertyTree::setBool)
      .def("setString", &MutablePropertyTree::setString)
      .def("setDouble", &MutablePropertyTree::setDouble)
      ;

  class_<BoostPropertyTree, bases<MutablePropertyTree> >("BoostPropertyTree", init<>())
      .def(init<std::string>("BoostPropertyTree( string baseNamespace )"))
      .def("loadXml", &BoostPropertyTree::loadXmlStr)
      .def("saveXml", &BoostPropertyTree::saveXmlStr)
      .def("loadIni", &BoostPropertyTree::loadIniStr)
      .def("saveIni", &BoostPropertyTree::saveIniStr)
      .def("loadInfo", &BoostPropertyTree::loadInfoStr)
      .def("saveInfo", &BoostPropertyTree::saveInfoStr)
      .def("update",
           static_cast<void(BoostPropertyTree::*)(const BoostPropertyTree&, bool, bool)>(
             &BoostPropertyTree::update
           ),
          "update(BoostPropertyTree & with, bool createIfNecessary, bool ignoreEmptyUpdates), update the property tree with another one")
      .def("updateWithEmptyUpdates",
           static_cast<void(BoostPropertyTree::*)(const BoostPropertyTree&, bool)>(
             &BoostPropertyTree::update
           ),
          "updateWithEmptyUpdates(BoostPropertyTree & with, bool createIfNecessary), update the property tree with another one, not ignoring empty updates")
      .def("updateOrCreate",
           static_cast<void(BoostPropertyTree::*)(const BoostPropertyTree&)>(
             &BoostPropertyTree::update
           ),
           "updateOrCreate(BoostPropertyTree & with), update the property tree with another one, creating nodes if necessary")
     ;
}
