void DebugPrintf(const char *fmt, ...) {
  va_list vl;
  va_start(vl, fmt);

  int size = _vscprintf(fmt, vl);
  if (size > 0) {
    char *buf = (char *)::HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size + 2);
    if (buf != nullptr) {
      _vsprintf_p(buf, size + 1, fmt, vl);
      ::OutputDebugStringA(buf);
      ::HeapFree(GetProcessHeap(), 0, buf);
    }
  }

  va_end(vl);
}