std::string FloatConstantGenerator::GenFloatConstantImpl(
    const FieldDef &field) const {
  const auto &constant = field.value.constant;
  T v;
  auto done = StringToNumber(constant.c_str(), &v);
  FLATBUFFERS_ASSERT(done);
  if (done) {
#if (!defined(_MSC_VER) || (_MSC_VER >= 1800))
    if (std::isnan(v)) return NaN(v);
    if (std::isinf(v)) return Inf(v);
#endif
    return Value(v, constant);
  }
  return "#";  // compile time error
}