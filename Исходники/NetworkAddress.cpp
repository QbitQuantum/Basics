bool
BNetworkAddress::IsMulticastGlobal() const
{
	switch (fAddress.ss_family) {
		case AF_INET6:
			return IN6_IS_ADDR_MC_GLOBAL(&((sockaddr_in6&)fAddress).sin6_addr);

		default:
			return false;
	}
}