bool MkvReader::GetFileSize() {
  if (m_file == NULL)
    return false;
#ifdef _MSC_VER
  int status = _fseeki64(m_file, 0L, SEEK_END);

  if (status)
    return false;  // error

  m_length = _ftelli64(m_file);
#else
  fseek(m_file, 0L, SEEK_END);
  m_length = ftell(m_file);
#endif
  assert(m_length >= 0);

  if (m_length < 0)
    return false;

#ifdef _MSC_VER
  status = _fseeki64(m_file, 0L, SEEK_SET);

  if (status)
    return false;  // error
#else
  fseek(m_file, 0L, SEEK_SET);
#endif

  return true;
}