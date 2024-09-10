// Look up an IP attribute in an ad, optionally fall back to an alternate
bool
getIpAddr( const char *ad_type,
		   const ClassAd *ad,
		   const char *attrname,
		   const char *attrold,
		   MyString &ip )
{
	MyString	tmp;

	// get the IP and port of the startd
	if ( !adLookup( ad_type, ad, attrname, attrold, tmp, true ) ) {
		return false;
	}

	// If no valid string, do our own thing..
	char* host;
	if ( ( tmp.Length() == 0 ) || (host = getHostFromAddr(tmp.Value())) == NULL  ) {
		dprintf (D_ALWAYS, "%sAd: Invalid IP address in classAd\n", ad_type );
		return false;
	}
	ip = host;
	free(host);

	return true;
}