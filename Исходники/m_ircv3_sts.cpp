	void SetPolicy(const std::string& newhost, unsigned long duration, unsigned int port, bool preload)
	{
		// To enforce an STS upgrade policy, servers MUST send this key to insecurely connected clients. Servers
		// MAY send this key to securely connected clients, but it will be ignored.
		std::string newplaintextpolicy("port=");
		newplaintextpolicy.append(ConvToStr(port));

		// To enforce an STS persistence policy, servers MUST send this key to securely connected clients. Servers
		// MAY send this key to all clients, but insecurely connected clients MUST ignore it.
		std::string newsecurepolicy("duration=");
		newsecurepolicy.append(ConvToStr(duration));

		// Servers MAY send this key to all clients, but insecurely connected clients MUST ignore it.
		if (preload)
			newsecurepolicy.append(",preload");

		// Apply the new policy.
		bool changed = false;
		if (!irc::equals(host, newhost))
		{
			ServerInstance->Logs.Log(MODNAME, LOG_DEBUG, "Changing STS SNI hostname from \"%s\" to \"%s\"", host.c_str(), newhost.c_str());
			host = newhost;
			changed = true;
		}

		if (plaintextpolicy != newplaintextpolicy)
		{
			ServerInstance->Logs.Log(MODNAME, LOG_DEBUG, "Changing plaintext STS policy from \"%s\" to \"%s\"", plaintextpolicy.c_str(), newplaintextpolicy.c_str());
			plaintextpolicy.swap(newplaintextpolicy);
			changed = true;
		}

		if (securepolicy != newsecurepolicy)
		{
			ServerInstance->Logs.Log(MODNAME, LOG_DEBUG, "Changing secure STS policy from \"%s\" to \"%s\"", securepolicy.c_str(), newsecurepolicy.c_str());
			securepolicy.swap(newsecurepolicy);
			changed = true;
		}

		// If the policy has changed then notify all clients via cap-notify.
		if (changed)
			NotifyValueChange();
	}