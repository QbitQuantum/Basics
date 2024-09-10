MyString convert_ipaddr_to_hostname(const condor_sockaddr& addr)
{
	MyString ret;
	MyString default_domain;
	if (!param(default_domain, "DEFAULT_DOMAIN_NAME")) {
		dprintf(D_HOSTNAME,
				"NO_DNS: DEFAULT_DOMAIN_NAME must be defined in your "
				"top-level config file\n");
		return ret;
	}

	ret = addr.to_ip_string();
	for (int i = 0; i < ret.Length(); ++i) {
		if (ret[i] == '.' || ret[i] == ':')
			ret.setChar(i, '-');
	}
	ret += ".";
	ret += default_domain;

	// Hostnames can't begin with -, as per RFC 1123
	// ipv6 zero-compression could cause this, esp. for the loopback addr
	if (ret[0] == '-') {
		ret = "0" + ret;
	}

	return ret;
}