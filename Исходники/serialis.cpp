bool TFile::Serialize(const uint64_t* buffer, size_t count) {
  return FWrite(buffer, sizeof(*buffer), count) == count;
}