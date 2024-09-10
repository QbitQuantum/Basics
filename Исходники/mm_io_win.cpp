size_t
mm_stdio_c::_write(const void *buffer,
                   size_t size) {
  HANDLE h_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
  if (INVALID_HANDLE_VALUE == h_stdout)
    return 0;

  DWORD file_type = GetFileType(h_stdout);
  bool is_console = false;
  if ((FILE_TYPE_UNKNOWN != file_type) && ((file_type & ~FILE_TYPE_REMOTE) == FILE_TYPE_CHAR)) {
    DWORD dummy;
    is_console = GetConsoleMode(h_stdout, &dummy);
  }

  if (is_console) {
    const std::wstring &w = to_wide(g_cc_stdio->utf8(std::string(static_cast<const char *>(buffer), size)));
    DWORD bytes_written   = 0;

    WriteConsoleW(h_stdout, w.c_str(), w.length(), &bytes_written, NULL);

    return bytes_written;
  }

  size_t bytes_written = fwrite(buffer, 1, size, stdout);
  fflush(stdout);

  m_cached_size = -1;

  return bytes_written;
}