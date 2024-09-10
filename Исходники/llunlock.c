int __ll_unlock(int handle, int offset, int length)
{
   if (UnlockFile((HANDLE)handle,offset,0,length,0))
      return 0 ;
   errno = GetLastError() ;
   return -1 ;
}