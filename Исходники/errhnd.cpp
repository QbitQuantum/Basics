void ErrorHandler::SysErrMsg()
{
#if defined(_WIN_32) && !defined(SFX_MODULE) && !defined(RAR_SILENT)
    #define STRCHR strchr
    #define ERRCHAR char
  ERRCHAR  *lpMsgBuf=NULL;
  int ErrType=GetLastError();
  if (ErrType!=0 && FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
              NULL,ErrType,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
              (LPTSTR)&lpMsgBuf,0,NULL))
  {
    ERRCHAR  *CurMsg=lpMsgBuf;
    while (CurMsg!=NULL)
    {
      while (*CurMsg=='\r' || *CurMsg=='\n')
        CurMsg++;
      if (*CurMsg==0)
        break;
      ERRCHAR *EndMsg=STRCHR(CurMsg,'\r');
      if (EndMsg==NULL)
        EndMsg=STRCHR(CurMsg,'\n');
      if (EndMsg!=NULL)
      {
        *EndMsg=0;
        EndMsg++;
      }
      Log(NULL,"\n%s",CurMsg);
      CurMsg=EndMsg;
    }
  }
  LocalFree( lpMsgBuf );
#endif
}