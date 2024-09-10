/**
Get the internet name of this host. Actually this will always return a null 
string with TCPIP 030 and onwards because the "name" of a mobile host
isn't really very meaningful - in practice the IP address is chosen dynamically
once you start doing real networking, at which time the ISP can resolve the 
IP address into a name of some sort if you really want.
@return 
@param name
@param size
*/
EXPORT_C int gethostname (char *name, size_t size)
	{
	int* perrno=__errno();
	RSocketServ ss;
	TInt err=ss.Connect(1);
	if (err==KErrNone)
		{
		RHostResolver r;
		err=r.Open(ss, AF_INET, KProtocolInetUdp);
		if (err==KErrNone)
			{
			TBuf<128> hostname;
			err=r.GetHostName(hostname);
			if (err==KErrNone)
				{
				if (size>(size_t)hostname.Length())
					{
					TPtr8 retval((TText8*)name,size);
					retval.Copy(hostname);
					retval.PtrZ();
					}
				else
					err=ENAMETOOLONG;
				}
			r.Close();
			}
		ss.Close();
		}
	return MapError(err,*perrno);
	}