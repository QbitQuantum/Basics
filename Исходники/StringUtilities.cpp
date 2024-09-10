std::wstring StringUtilities::Format(const wchar_t* format, ...) {
  va_list args;
  va_start(args, format);
  size_t buffer_size = _vscwprintf(format, args);
  std::vector<wchar_t> buffer(buffer_size + 1);
  _vsnwprintf_s(&buffer[0], buffer.size(), buffer_size + 1, format, args);
  va_end(args);
  std::wstring formatted = &buffer[0];
  return formatted;
}