int cdecl vMessage (UINT type, int title, LPCTSTR text, LPCTSTR fmt, va_list arg)
{
   return vMessage (type, (LONG)title, PtrToLong(text), fmt, arg);
}