void addr_parse_hostspec(char *hoststr, size_t hoststr_sz,
		char *service, size_t service_sz, const char *hostspec)
{
	strNcpy(hoststr, hostspec + (hostspec[0] == '['), hoststr_sz);
	char *ptr = strchr(hoststr, ']');
	if (!ptr)
		ptr = hoststr;
	else
		*ptr++ = '\0';

	ptr = strchr(ptr, ':');
	if (ptr) {
		if (service && service_sz)
			strNcpy(service, ptr+1, service_sz);
		*ptr = '\0';
	} else {
		if (service && service_sz)
			service[0] = '\0';
	}
}