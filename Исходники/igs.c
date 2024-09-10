/*
 * str_to_inet_gw:
 * The syntax of `str' is IP:devname, i.e. 192.168.1.1:eth0.
 * str_to_inet_gw() stores the IP in `gw'.
 * In `*dev' is returned the pointer to a newly allocated string containing
 * the device name.
 * On error -1 is returned.
 */
int
str_to_inet_gw(char *str, inet_prefix * gw, char **dev)
{
	char *buf;

	setzero(dev, IFNAMSIZ);

	/* Copy :devname in `dev' */
	if (!(buf = rindex(str, ':')))
		return -1;
	*buf = 0;
	buf++;
	if (!*buf)
		/* No device was specified */
		return -1;

	if (strlen(buf) >= IFNAMSIZ)
		/* It is too long, truncate it */
		buf[IFNAMSIZ - 1] = 0;
	*dev = xstrndup(buf, IFNAMSIZ);

	/* Extract the IP from the first part of `str' */
	if (str_to_inet(str, gw))
		return -1;

	return 0;
}