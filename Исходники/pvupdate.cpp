bool InternetConnected (void)
{
  DWORD       flags ;

  BOOL result = InternetGetConnectedState (&flags, 0) ;
  if ((flags & INTERNET_CONNECTION_OFFLINE) != 0)
    return (false) ;
  return (result != 0) ;
}