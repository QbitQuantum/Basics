const char* wyDevice::getDeviceId() {
	// Get the buffer length required for IP_ADAPTER_INFO.
	ULONG bufLen = 0;
	BYTE* buffer = 0;
	if(GetAdaptersInfo(0, &bufLen) == ERROR_BUFFER_OVERFLOW) {
		// Now the BufferLength contain the required buffer length.
		// Allocate necessary buffer.
		buffer = new BYTE[bufLen];

		// Get the Adapter Information.
		PIP_ADAPTER_INFO adapterInfo = reinterpret_cast<PIP_ADAPTER_INFO>(buffer);
		GetAdaptersInfo(adapterInfo, &bufLen);

		// Iterate the network adapters and print their MAC address.
		if(adapterInfo) {
			// Assuming pAdapterInfo->AddressLength is 6.
			sprintf(sIMEI, "%02x:%02x:%02x:%02x:%02x:%02x",
				adapterInfo->Address[0],
				adapterInfo->Address[1],
				adapterInfo->Address[2],
				adapterInfo->Address[3],
				adapterInfo->Address[4],
				adapterInfo->Address[5]);
		}

		// make md5 for mac address
		const char* md5 = wyMD5::md5(sIMEI);
		memcpy(sIMEI, md5, strlen(md5));
		wyFree((void*)md5);

		// release buffer
		delete[] buffer;

		// return
		return sIMEI;
	} else {
		return NULL;
	}
}