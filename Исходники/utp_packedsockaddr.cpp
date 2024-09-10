// #define addrfmt(x, s) x.fmt(s, sizeof(s))
cstr PackedSockAddr::fmt(str s, size_t len) const
{
	memset(s, 0, len);
	const byte family = get_family();
	str i;
	if (family == AF_INET) {
		INET_NTOP(family, (uint32*)&_sin4, s, len);
		i = s;
		while (*++i) {}
	} else {
		i = s;
		*i++ = '[';
		INET_NTOP(family, (in6_addr*)&_in._in6addr, i, len-1);
		while (*++i) {}
		*i++ = ']';
	}
	snprintf(i, len - (i-s), ":%u", _port);
	return s;
}