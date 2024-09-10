__int64 NSISCALL _dodecomp(__int64 offset, HANDLE hFileOut, unsigned char *outbuf, int outbuflen)
{
  DWORD r;
  __int64 input_len;
  __int64 retval;
  if (offset>=0)
  {
    dbd_pos=g_blocks[NB_DATA].offset+offset;
    SetFilePointerEx(dbd_hFile,(LARGE_INTEGER*)&dbd_pos,NULL,FILE_BEGIN);
  }
  retval=__ensuredata(sizeof(__int64));
  if (retval<0) return retval;

  if (!ReadFile(dbd_hFile,(LPVOID)&input_len,sizeof(__int64),&r,NULL) || r!=sizeof(__int64)) return -3;
  dbd_pos+=sizeof(__int64);

  retval=__ensuredata(input_len);
  if (retval < 0) return retval;

  if (!outbuf)
  {
    while (input_len > 0)
    {
      DWORD t;
      DWORD l=min(input_len,IBUFSIZE);
      if (!ReadFile(dbd_hFile,(LPVOID)_inbuffer,l,&r,NULL) || l != r) return -3;
      if (!WriteFile(hFileOut,_inbuffer,r,&t,NULL) || t != l) return -2;
      retval+=r;
      input_len-=r;
      dbd_pos+=r;
    }
  }
  else
  {
    if (!ReadFile(dbd_hFile,(LPVOID)outbuf,min(input_len,outbuflen),&r,NULL)) return -3;
    retval=r;
    dbd_pos+=r;
  }
  return retval;
}