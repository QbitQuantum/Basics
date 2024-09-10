void write_str(FileHandle& fh, const std::string& str) {
  const auto len = str.size();
  CHECK(fh.fwrite(str.c_str(), sizeof(char), len) == len);
}