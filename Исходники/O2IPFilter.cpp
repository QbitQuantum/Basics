uint
O2IPFilter::
filtering(ulong ip, const wstrarray &hostnames)
{
	uint ret = DefaultFlag;

	Lock();
	for (uint i = 0; i < records.size(); i++) {
		if (records[i].host.empty()) {
			if ((ip & records[i].mask) == records[i].ip)
				ret = records[i].flag;
		}
		else if (!hostnames.empty()) {
			for (uint j = 0; j < hostnames.size(); j++) {
				int offset = hostnames[j].size() - records[i].host.size();
				if (offset >= 0 && wcsncmp(&hostnames[j][offset], records[i].host.c_str(), records[i].host.size()) == 0)
					ret = records[i].flag;
			}
		}
	}
	Unlock();

	return (ret);
}