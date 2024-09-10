bool condor_sockaddr::is_private_network() const
{
	if (is_ipv4()) {
		static bool initialized = false;
		static condor_netaddr p10;
		static condor_netaddr p172_16;
		static condor_netaddr p192_168;
		if(!initialized) {
			p10.from_net_string("10.0.0.0/8");
			p172_16.from_net_string("172.16.0.0/12");
			p192_168.from_net_string("192.168.0.0/16");
			initialized = true;
		}

		return p10.match(*this) || p172_16.match(*this) || p192_168.match(*this);
	}
	else if (is_ipv6()) {
		return IN6_IS_ADDR_LINKLOCAL(&v6.sin6_addr);
	}
	else {

	}
	return false;
}