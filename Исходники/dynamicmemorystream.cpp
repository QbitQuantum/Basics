int DynamicMemoryStream::PrintF(const char* Str, ...) const {
  va_list Args;
  int Length = 0;
  char* Buffer = nullptr;
  int RetVal = 0;

  va_start(Args, Str);
  Length = VSPRINTF_COUNT(Str, Args) + 1;
  Buffer =
      new char[Length];  // TODO: Pool this instead of dynamically allocating
  VSPRINTF(Buffer, Length, Str, Args);

  RetVal = Write(Length - 1, Buffer);

  SafeDelete(Buffer);
  return RetVal;
}