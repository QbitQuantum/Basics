MANTID_API_DLL Mantid::API::IMDEventWorkspace_const_sptr
IPropertyManager::getValue<Mantid::API::IMDEventWorkspace_const_sptr>(
    const std::string &name) const {
  PropertyWithValue<Mantid::API::IMDEventWorkspace_const_sptr> *prop =
      dynamic_cast<
          PropertyWithValue<Mantid::API::IMDEventWorkspace_const_sptr> *>(
          getPointerToProperty(name));
  if (prop) {
    return prop->operator()();
  } else {
    // Every other class with this behaviour allows you to get a shared_ptr<T>
    // property as a shared_ptr<const T>. This class should be consistent, so
    // try that:
    PropertyWithValue<Mantid::API::IMDEventWorkspace_sptr> *nonConstProp =
        dynamic_cast<PropertyWithValue<Mantid::API::IMDEventWorkspace_sptr> *>(
            getPointerToProperty(name));
    if (nonConstProp) {
      return nonConstProp->operator()();
    } else {
      std::string message =
          "Attempt to assign property " + name +
          " to incorrect type. Expected const shared_ptr<IMDEventWorkspace>.";
      throw std::runtime_error(message);
    }
  }
}