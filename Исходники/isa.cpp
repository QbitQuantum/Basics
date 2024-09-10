std::string Isa::GetFullName() const {
  std::stringstream full_name;
  full_name << GetVendor() << ":" << GetArchitecture() << ":"
            << GetMajorVersion() << ":" << GetMinorVersion() << ":"
            << GetStepping();
  return full_name.str();
}