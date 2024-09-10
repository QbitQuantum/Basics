static int clear_line() {
  HANDLE handle;
  CONSOLE_SCREEN_BUFFER_INFO info;
  COORD coord;
  DWORD written;

  handle = (HANDLE)_get_osfhandle(fileno(stderr));
  if (handle == INVALID_HANDLE_VALUE)
    return -1;

  if (!GetConsoleScreenBufferInfo(handle, &info))
    return -1;

  coord = info.dwCursorPosition;
  if (coord.Y <= 0)
    return -1;

  coord.X = 0;

  if (!SetConsoleCursorPosition(handle, coord))
    return -1;

  if (!FillConsoleOutputCharacterW(handle, 0x20, info.dwSize.X, coord, &written))
    return -1;

  return 0;
}