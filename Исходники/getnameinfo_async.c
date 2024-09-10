/*
 * Write the numeric address
 */
static int
_numerichost(struct asr_query *as)
{
	unsigned int	ifidx;
	char		scope[IF_NAMESIZE + 1], *ifname;
	void		*addr;
	char		*buf = as->as.ni.hostname;
	size_t		 buflen = as->as.ni.hostnamelen;

	if (as->as.ni.sa.sa.sa_family == AF_INET)
		addr = &as->as.ni.sa.sain.sin_addr;
	else
		addr = &as->as.ni.sa.sain6.sin6_addr;

	if (inet_ntop(as->as.ni.sa.sa.sa_family, addr, buf, buflen) == NULL)
		return (-1); /* errno set */

	if (as->as.ni.sa.sa.sa_family == AF_INET6 &&
	    as->as.ni.sa.sain6.sin6_scope_id) {

		scope[0] = SCOPE_DELIMITER;
		scope[1] = '\0';

		ifidx = as->as.ni.sa.sain6.sin6_scope_id;
		ifname = NULL;

		if (IN6_IS_ADDR_LINKLOCAL(&as->as.ni.sa.sain6.sin6_addr) ||
		    IN6_IS_ADDR_MC_LINKLOCAL(&as->as.ni.sa.sain6.sin6_addr) ||
		    IN6_IS_ADDR_MC_NODELOCAL(&as->as.ni.sa.sain6.sin6_addr))
			ifname = if_indextoname(ifidx, scope + 1);

		if (ifname == NULL)
			snprintf(scope + 1, sizeof(scope) - 1, "%u", ifidx);

		strlcat(buf, scope, buflen);
	}

	return (0);
}