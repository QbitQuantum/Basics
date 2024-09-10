void JsonWriter::WriteRaw(const char *name, const char *raw,
                          size_t raw_length) {
  WriteRaw(name, std::string(raw, raw_length));
}