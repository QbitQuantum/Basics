void UNIX_PROVIDER::__initialize(CIMOMHandle &ch)
{
   _cimomHandle = ch;

  // call platform-specific routine to get values
  if (getHostName(_hostName))
  {
  	// LOG HOSTNAME FETCH ERROR
  }
  if (getOSName(_osName))
  {
  	// LOG HOSTNAME FETCH ERROR
  }
  return;
}  /* initialize */