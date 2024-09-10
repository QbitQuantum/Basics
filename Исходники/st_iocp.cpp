int IOCP::Create(void)
{
  int iHandle;
  HANDLE hnd;

  hnd = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
  if ( hnd == NULL )
  {
    return -1;
  }

  iHandle = UniqueCount :: GetUniqueCount();
  iocp.insert( MapWordToPtr::value_type( iHandle, hnd ) );

  return iHandle;
}