int CXbtFile::Stat(const CURL& url, struct __stat64* buffer)
{
  memset(buffer, 0, sizeof(struct __stat64));

  // check if the file exists
  CXBTFReaderPtr reader;
  CXBTFFile file;
  if (!GetReaderAndFile(url, reader, file))
  {
    // check if the URL points to the XBT file itself
    if (!url.GetFileName().empty() || !CFile::Exists(url.GetHostName()))
      return -1;

    // stat the XBT file itself
    if (XFILE::CFile::Stat(url.GetHostName(), buffer) != 0)
      return -1;

    buffer->st_mode = _S_IFDIR;
    return 0;
  }

  // stat the XBT file itself
  if (XFILE::CFile::Stat(url.GetHostName(), buffer) != 0)
    return -1;

  buffer->st_size = file.GetUnpackedSize();

  return 0;
}