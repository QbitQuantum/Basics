int64_t FSeek(HANDLE h, int64_t pos, int method)
{
  LONG hi32 = HI32(pos);
  LONG lo32 = ::SetFilePointer(h, LO32(pos), &hi32, method);
  if (lo32 == INVALID_SET_FILE_POINTER && ::GetLastError())
    return -1;
  else
    return MAKEINT64(lo32, hi32);
}