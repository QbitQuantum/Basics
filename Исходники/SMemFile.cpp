BYTE* CSMemFile::Realloc(BYTE* lpOldMem, SIZE_T nBytes)
{
  if (nBytes == 0) {
    trashMemory(lpOldMem, m_size);
    Free(lpOldMem);
    m_size = 0;
    return NULL;
  }

  size_t old_size = _msize((void *)lpOldMem);
  ASSERT(m_size == old_size);
  BYTE* lpNewMem = (BYTE *)malloc(nBytes);

  if (lpNewMem == NULL) {
    trashMemory(lpOldMem, old_size);
    free(lpOldMem);
    m_size = 0;
    return NULL;
  }

  memcpy_s((void *)lpNewMem, nBytes, (void *)lpOldMem, old_size);
  trashMemory(lpOldMem, old_size);
  free(lpOldMem);

  m_size = nBytes;
  return lpNewMem;
}