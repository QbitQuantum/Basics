void SaveAsJob::doSave() {
  FILE *dst = MKFOPEN(m_newName, _T("wb"));
  try {
    ByteArray buffer;
    for(m_fileIndex = 0; (m_fileIndex < m_size) && !isInterrupted(); m_fileIndex += buffer.size()) {
      m_src.getBytes(m_fileIndex, 0x4000, buffer);
      if(buffer.size()) {
        FWRITE(buffer.getData(), 1, buffer.size(), dst);
      }
    }
    if(isInterrupted()) {
      throwException(_T("Save cancelled"));
    }
    fclose(dst);
    dst = NULL;
  } catch(...) {
    if(dst) {
      fclose(dst);
    }
    unlink(m_newName);
    m_ok = false;
    throw;
  }
}