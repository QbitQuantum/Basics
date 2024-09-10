v8_inspector::StringView toV8InspectorStringView(const StringView& string) {
  if (string.isNull())
    return v8_inspector::StringView();
  if (string.is8Bit())
    return v8_inspector::StringView(
        reinterpret_cast<const uint8_t*>(string.characters8()),
        string.length());
  return v8_inspector::StringView(
      reinterpret_cast<const uint16_t*>(string.characters16()),
      string.length());
}