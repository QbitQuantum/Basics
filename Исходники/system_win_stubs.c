CAMLprim value win_set_console_output_cp (value cp) {
  BOOL res;
  res = SetConsoleOutputCP (Int_val (cp));
  if (res == 0) {
    win32_maperr (GetLastError ());
    uerror("set_console_cp", Nothing);
  }
  return (Val_unit);
}