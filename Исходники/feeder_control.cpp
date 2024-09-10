BOOL ComIO::CheckCom(int i)
{
  HANDLE hCurCom = OpenCommPort(i);
  if(hCurCom == NULL)
    return 0;
  CommPort_Init(hCurCom);
      hCom = hCurCom;
      return 1;
  /*
  int  Ret;
  Ret = CommPort_Write(hCurCom, "sta\r\n");
  if(Ret == 1)
  {
    char  Buf[0x10];
    Sleep(50);
    Ret = CommPort_Read(hCurCom, Buf, 0x10);
    if(Ret == 1)
    {
      hCom = hCurCom;
      return 1;
    }
  }
  CommPort_Close(hCurCom);
  return 0;*/
}