bool Configurator::readConfiguration (const char *filename)
{
	std::ifstream file(filename == 0 ? Configurator::filename : filename);
	if (!file.good())
		return false;

	int version;
	if (!readInt(file, version) || (version != 1 && version != 2 && version != 3))
		return false;

	int routerCount;
	if (!readInt(file, routerCount) || routerCount < 0)
		return false;
	
	for (int i = 0; i != routerCount; ++i)
	{
		std::string interface;
		int vrid;
		int addressFamily;
		int priority;
		int interval;
		bool accept;
		bool preempt;
		bool enabled;
		int flags;
		IpAddress primaryIp;
		int addressCount;
		IpSubnetSet subnets;
		std::string masterCommand;
		std::string backupCommand;
		int vlanId;

		// Read data
		if (
				!readString(file, interface)
				|| !readInt(file, vrid)
				|| !readInt(file, addressFamily)
				|| !readInt(file, priority)
				|| !readInt(file, interval)
				|| !readBoolean(file, accept)
				|| !readBoolean(file, preempt)
				|| !readBoolean(file, enabled)
				|| !readInt(file, flags))
		{
			return false;
		}

		if (flags & FLAG_HAS_PRIMARY_IP_ADDRESS)
		{
			if (!readIp(file, primaryIp))
				return false;
		}

		if (version > 1)
		{
			if (!readString(file, masterCommand) || !readString(file, backupCommand))
				return false;
		}

		if (version > 2)
		{
			if (!readInt(file, vlanId))
				return false;
		}

		if (!readInt(file, addressCount))
			return false;

		for (int j = 0; j != addressCount; ++j)
		{
			IpSubnet subnet;
			if (!readSubnet(file, subnet))
				return false;

			subnets.insert(subnet);
		}

		// Sanitize

		if (vrid < 1 || vrid > 255)
		{
			// TODO - Add to log
			continue;
		}

		if (priority < 1 || priority > 255)
		{
			// TODO - Add to log
			continue;
		}

		if (addressFamily != AF_INET && addressFamily != AF_INET6)
		{
			// TODO - Add to log
			continue;
		}

		if (interval % 10 != 0 || interval < 10 || interval > 40950)
		{
			// TODO - Add to log
			continue;
		}

		int ifIndex = if_nametoindex(interface.c_str());
		if (ifIndex <= 0)
		{
			// TODO - Add to log
			continue;
		}

		// Create service

		VrrpService *service = VrrpManager::getService(ifIndex, vrid, vlanId, addressFamily, true);
		if (service == 0)
		{
			// TODO - Add to log
			continue;
		}

		service->setPriority(priority);
		service->setAdvertisementInterval(interval / 10);
		service->setAcceptMode(accept);
		service->setPreemptMode(preempt);
		if (flags & FLAG_HAS_PRIMARY_IP_ADDRESS)
			service->setPrimaryIpAddress(primaryIp);
		service->setMasterCommand(masterCommand);
		service->setBackupCommand(backupCommand);
		for (IpSubnetSet::const_iterator subnet = subnets.begin(); subnet != subnets.end(); ++subnet)
		{
			service->addIpAddress(*subnet);
		}
		if (enabled)
			service->enable();
		else
			service->disable();
	}

	return true;
}