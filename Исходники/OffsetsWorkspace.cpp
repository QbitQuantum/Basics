 template<> DLLExport
 Mantid::DataObjects::OffsetsWorkspace_const_sptr IPropertyManager::getValue<Mantid::DataObjects::OffsetsWorkspace_const_sptr>(const std::string &name) const
 {
   PropertyWithValue<Mantid::DataObjects::OffsetsWorkspace_sptr>* prop =
     dynamic_cast<PropertyWithValue<Mantid::DataObjects::OffsetsWorkspace_sptr>*>(getPointerToProperty(name));
   if (prop)
   {
     return prop->operator()();
   }
   else
   {
     std::string message = "Attempt to assign property "+ name +" to incorrect type. Expected const OffsetsWorkspace.";
     throw std::runtime_error(message);
   }
 }