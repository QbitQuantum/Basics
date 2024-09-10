/*
 * static char *
 * inet_net_ntop_ipv4(src, bits, dst, size)
 *	convert IPv4 network number from network to presentation format.
 *	generates CIDR style result always.
 * return:
 *	pointer to dst, or NULL if an error occurred (check errno).
 * note:
 *	network byte order assumed.  this means 192.5.5.240/28 has
 *	0b11110000 in its fourth octet.
 * author:
 *	Paul Vixie (ISC), July 1996
 */
static char *
inet_net_ntop_ipv4(const u_char *src, int bits, char *dst, size_t size)
{
	char *odst = dst;
	char *t;
	u_int m;
	int b;

	if (bits < 0 || bits > 32) {
		errno = EINVAL;
		return (NULL);
	}

	if (bits == 0) {
		if (size < sizeof "0")
			goto emsgsize;
		*dst++ = '0';
		size--;
		*dst = '\0';
	}

	/* Format whole octets. */
	for (b = bits / 8; b > 0; b--) {
		if (size <= sizeof "255.")
			goto emsgsize;
		t = dst;
		dst += SPRINTF((dst, "%u", *src++));
		if (b > 1) {
			*dst++ = '.';
			*dst = '\0';
		}
		size -= (size_t)(dst - t);
	}

	/* Format partial octet. */
	b = bits % 8;
	if (b > 0) {
		if (size <= sizeof ".255")
			goto emsgsize;
		t = dst;
		if (dst != odst)
			*dst++ = '.';
		m = ((1 << b) - 1) << (8 - b);
		dst += SPRINTF((dst, "%u", *src & m));
		size -= (size_t)(dst - t);
	}

	/* Format CIDR /width. */
	if (size <= sizeof "/32")
		goto emsgsize;
	dst += SPRINTF((dst, "/%u", bits));
	return (odst);

 emsgsize:
	errno = EMSGSIZE;
	return (NULL);
}