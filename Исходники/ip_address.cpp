CStr CIpAddress::GetFullHostName()
{_STT();
	CStr sDomain = GetDomainName();
	if ( sDomain.Length() )
		return GetHostName() << oexT( "." ) << sDomain;
	return GetHostName();
}