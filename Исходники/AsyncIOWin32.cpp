AsyncIO& AsyncIO::operator=(AsyncIO&& other) {
  if (*this) {
    if (CancelIoEx(m_fh, nullptr))
      waitForCompletion();
    CloseHandle(m_fh);
  }
  m_fh = other.m_fh;
  other.m_fh = INVALID_HANDLE_VALUE;
  m_queue = std::move(other.m_queue);
  m_maxBlock = other.m_maxBlock;
  return *this;
}