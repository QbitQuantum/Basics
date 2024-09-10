struct servent *wp_getservbyport (int prot, const char *proto)
{
	struct servent *p;
	if ((p = getservbyport (prot, proto)) == NULL)
		wp_warning ("getservbyport() error");
	return p;
}