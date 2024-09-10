	void BroadcastReceiver::WriteRecentEndpoints(const std::string& filename, uint8_t threshold) const
	{
		std::ofstream outFile;
		if(filename.compare("") == 0)
			outFile.open(mRecentFilename, std::ios::trunc);
		else
			outFile.open(filename, std::ios::trunc);

		if(!outFile.is_open()) {
			Trace(ZONE_ERROR, "Open file to write recent endpoints failed\n");
			return;
		}
		// write to file
		for(auto it = mIpTable.begin(); it != mIpTable.end(); it++) {
			const auto currentEndpoint = it->second;
			if(currentEndpoint.GetScore() >= threshold) {
				//TODO refactor this but then we have to change the CLI implementation
				outFile << (int)(currentEndpoint.GetScore()) << ' ' << std::hex << currentEndpoint.GetIp() << ' ' << std::dec << currentEndpoint.GetPort() << ' ' << currentEndpoint.GetDeviceId() << '\n';
			}
		}
		outFile.close();
	}