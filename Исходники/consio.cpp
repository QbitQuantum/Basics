static void cvt_wprintf(FILE *dest,const wchar *fmt,va_list arglist)
{
  // This buffer is for format string only, not for entire output,
  // so it can be short enough.
  wchar fmtw[1024];
  PrintfPrepareFmt(fmt,fmtw,ASIZE(fmtw));
#ifdef _WIN_ALL
  safebuf wchar Msg[MaxMsgSize];
  if (dest==stdout && StdoutRedirected || dest==stderr && StderrRedirected)
  {
    // Avoid Unicode for redirect in Windows, it does not work with pipes.
    vswprintf(Msg,ASIZE(Msg),fmtw,arglist);
    safebuf char MsgA[MaxMsgSize];
    WideToChar(Msg,MsgA,ASIZE(MsgA));
    CharToOemA(MsgA,MsgA); // Console tools like 'more' expect OEM encoding.

    // We already converted \n to \r\n above, so we use WriteFile instead
    // of C library to avoid unnecessary additional conversion.
    HANDLE hOut=GetStdHandle(dest==stdout ? STD_OUTPUT_HANDLE:STD_ERROR_HANDLE);
    DWORD Written;
    WriteFile(hOut,MsgA,(DWORD)strlen(MsgA),&Written,NULL);
    return;
  }
  // MSVC2008 vfwprintf writes every character to console separately
  // and it is too slow. We use direct WriteConsole call instead.
  vswprintf(Msg,ASIZE(Msg),fmtw,arglist);
  HANDLE hOut=GetStdHandle(dest==stderr ? STD_ERROR_HANDLE:STD_OUTPUT_HANDLE);
  DWORD Written;
  WriteConsole(hOut,Msg,(DWORD)wcslen(Msg),&Written,NULL);
#else
  vfwprintf(dest,fmtw,arglist);
  // We do not use setbuf(NULL) in Unix (see comments in InitConsole).
  fflush(dest);
#endif
}