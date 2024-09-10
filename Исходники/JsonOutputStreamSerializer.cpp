ISerializer& JsonOutputStreamSerializer::operator()(int32_t& value, const std::string& name) {
  int64_t v = static_cast<int64_t>(value);
  return operator()(v, name);
}