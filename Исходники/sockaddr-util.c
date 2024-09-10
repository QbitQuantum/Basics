static sockaddr_union *
unmap_v4mapped(
    sockaddr_union *sa,
    sockaddr_union *tmp)
{
    if (SU_GET_FAMILY(sa) == AF_INET6 && IN6_IS_ADDR_V4MAPPED(&sa->sin6.sin6_addr)) {
	SU_INIT(tmp, AF_INET);
	SU_SET_PORT(tmp, SU_GET_PORT(sa));
	/* extract the v4 address from byte 12 of the v6 address */
	memcpy(&tmp->sin.sin_addr.s_addr,
	       &sa->sin6.sin6_addr.s6_addr[12],
	       sizeof(struct in_addr));
	return tmp;
    }

    return sa;
}