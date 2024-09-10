	json SessionApi::getSystemInfo(const string& aIp) noexcept {
		return {
			{ "path_separator", PATH_SEPARATOR_STR },
			{ "network_type", getNetworkType(aIp) },
			{ "platform", getPlatform() },
			{ "hostname", getHostname() },
		};
	}