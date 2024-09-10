  void get_text(TCHAR *text, size_t max_length) {
#ifndef USE_GDI
    value.copy(text, std::min(max_length - 1, value.length()));
#else
    ::GetWindowText(hWnd, text, max_length);
#endif
  }