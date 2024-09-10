MANTID_API_DLL Mantid::API::IMDWorkspace_const_sptr
IPropertyManager::getValue<Mantid::API::IMDWorkspace_const_sptr>(
    const std::string &name) const {
  PropertyWithValue<Mantid::API::IMDWorkspace_sptr> *prop =
      dynamic_cast<PropertyWithValue<Mantid::API::IMDWorkspace_sptr> *>(
          getPointerToProperty(name));
  if (prop) {
    return prop->operator()();
  } else {
    std::string message = "Attempt to assign property " + name +
                          " to incorrect type. Expected const IMDWorkspace.";
    throw std::runtime_error(message);
  }
}