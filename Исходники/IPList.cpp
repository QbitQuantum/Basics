// read in a list linking IPs, subnets & IP ranges to filter groups
bool IPList::readIPMelangeList(const char *filename)
{
	// load in the list file
	std::ifstream input ( filename );
	if (!input) {
		if (!is_daemonised) {
			std::cerr << "Error reading file (does it exist?): " << filename << std::endl;
		}
		syslog(LOG_ERR, "%s%s","Error reading file (does it exist?): ",filename);
		return false;
	}

	// compile regexps for determining whether a list entry is an IP, a subnet (IP + mask), or a range
	RegExp matchIP, matchSubnet, matchRange;
#ifdef HAVE_PCRE
	matchIP.comp("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
	matchSubnet.comp("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}/\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
	matchRange.comp("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}-\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
#else
	matchIP.comp("^[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}$");
	matchSubnet.comp("^[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}/[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}$");
	matchRange.comp("^[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}-[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}$");
#endif

	// read in the file
	String line;
	char buffer[ 2048 ];
	while (input) {
		if (!input.getline(buffer, sizeof( buffer ))) {
			break;
		}
		// ignore comments
		if (buffer[0] == '#')
			continue;
		// ignore blank lines
		if (strlen(buffer) < 7)
			continue;
		line = buffer;
#ifdef DGDEBUG
		std::cout << "line: " << line << std::endl;
#endif
		// store the IP address (numerically, not as a string) and filter group in either the IP list, subnet list or range list
		if (matchIP.match(line.toCharArray())) {
			struct in_addr address;
			if (inet_aton(line.toCharArray(), &address)) {
				uint32_t addr = ntohl(address.s_addr);
				iplist.push_back(addr);
			}
		}
		else if (matchSubnet.match(line.toCharArray())) {
			struct in_addr address;
			struct in_addr addressmask;
			String subnet(line.before("/"));
			String mask(line.after("/"));
			if (inet_aton(subnet.toCharArray(), &address) && inet_aton(mask.toCharArray(), &addressmask)) {
				ipl_subnetstruct s;
				uint32_t addr = ntohl(address.s_addr);
				s.mask = ntohl(addressmask.s_addr);
				// pre-mask the address for quick comparison
				s.maskedaddr = addr & s.mask;
				ipsubnetlist.push_back(s);
			}
		}
		else if (matchRange.match(line.toCharArray())) {
			struct in_addr addressstart;
			struct in_addr addressend;
			String start(line.before("-"));
			String end(line.after("-"));
			if (inet_aton(start.toCharArray(), &addressstart) && inet_aton(end.toCharArray(), &addressend)) {
				ipl_rangestruct r;
				r.startaddr = ntohl(addressstart.s_addr);
				r.endaddr = ntohl(addressend.s_addr);
				iprangelist.push_back(r);
			}
		}
		// hmmm. the line didn't match any of our regular expressions.
		// assume it's a hostname.
		else {
			line.toLower();
			hostlist.push_back(line);
		}
	}
	input.close();
#ifdef DGDEBUG
	std::cout << "starting sort" << std::endl;
#endif
	std::sort(iplist.begin(), iplist.end());
	std::sort(hostlist.begin(), hostlist.end());
#ifdef DGDEBUG
	std::cout << "sort complete" << std::endl;
	std::cout << "ip list dump:" << std::endl;
	std::vector<uint32_t>::iterator i = iplist.begin();
	while (i != iplist.end()) {
		std::cout << "IP: " << *i << std::endl;
		++i;
	}
	std::cout << "subnet list dump:" << std::endl;
	std::list<ipl_subnetstruct>::iterator j = ipsubnetlist.begin();
	while (j != ipsubnetlist.end()) {
		std::cout << "Masked IP: " << j->maskedaddr << " Mask: " << j->mask << std::endl;
		++j;
	}
	std::cout << "range list dump:" << std::endl;
	std::list<ipl_rangestruct>::iterator k = iprangelist.begin();
	while (k != iprangelist.end()) {
		std::cout << "Start IP: " << k->startaddr << " End IP: " << k->endaddr << std::endl;
		++k;
	}
	std::cout << "host list dump:" << std::endl;
	std::vector<String>::iterator l = hostlist.begin();
	while (l != hostlist.end()) {
		std::cout << "Hostname: " << *l << std::endl;
		++l;
	}
#endif
	return true;
}