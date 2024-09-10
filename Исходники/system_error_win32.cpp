static std::string GetErrorMessage(DWORD error) {
  std::string message;

  LPVOID buffer = NULL;
  DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS;
  DWORD lang_id = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);

  DWORD result = FormatMessageA(flags, NULL, error, lang_id,
                                reinterpret_cast<LPSTR>(&buffer),
                                0, NULL);
  if (result > 0) {
    message.assign(StripNewLine(reinterpret_cast<char*>(buffer)));
  }

  LocalFree(buffer);

  return message;
}