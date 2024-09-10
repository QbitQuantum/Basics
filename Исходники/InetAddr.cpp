void	InetAddr::set(char	*straddr, int portnum)
{
	reset();	
	inet_addr_.sin_family = AF_INET;
	inet_addr_.sin_port = htons(portnum);
		
	if (straddr != NULL) {
		if (_isIPnumber(straddr)) {
			inet_addr_.sin_addr.s_addr	= inet_addr(straddr);
			STRNCPY(ipaddr, straddr, _LEN_INADDR);
		}
		else {
			STRNCPY(hostname, straddr, _LEN_HOSTNAME);
			struct hostent	*hent;
			hent = gethostbyname(straddr);
			if (hent==NULL) {
				inet_addr_.sin_addr.s_addr	= htonl(INADDR_ANY);
			}
			else {
				memcpy(& (inet_addr_.sin_addr.s_addr), hent->h_addr, hent->h_length);
				STRNCPY(ipaddr, inet_ntoa( *( (struct in_addr *) hent->h_addr ) ), _LEN_INADDR);
			}	
		}
	}
	else
		inet_addr_.sin_addr.s_addr	= htonl(INADDR_ANY);
}