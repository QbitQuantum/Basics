int32_t CWelsTraceWinDgb::WriteString (int32_t iLevel, const char* pStr) {
  OutputDebugStringA (pStr);

  return strlen (pStr);
}