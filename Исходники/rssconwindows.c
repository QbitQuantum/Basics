bool rssconwindowsOpen(Rsscon* rsscon) {
	bool createFile(const char* device, RssconwindowsPortdata* pdata);
	bool setCommConfiguration(const char*, RssconwindowsPortdata*, DCB*);
	bool setCommState(const char*, RssconwindowsPortdata*, DCB*);
	bool handshakeOff(RssconwindowsPortdata* portdata);
	bool readTimeoutBlocking(RssconwindowsPortdata* pdata);
	bool readTimeoutNonblocking(RssconwindowsPortdata* pdata);

	assert(rsscon != NULL);
	assert(rsscon->portdata != NULL);
	RssconwindowsPortdata* pdata = (RssconwindowsPortdata*) rsscon->portdata;

	LOG4C_CATEGORY log = get_log(LOG_CATEGORY);
	log_debug(log, "open windows device for rsscon %d.", rsscon);

	rssconSetLastError(rsscon, RSSCON_ERROR_NOERROR);

	const char* device = rssconGetDevice(rsscon);
	log_debug(log, "create file for device %s.", device);
	if (!createFile(device, pdata)) {
		rssconSetLastError(rsscon, RSSCON_ERROR_OPENDEVICE);
		return false;
	}

	DCB port = {0};
	port.DCBlength = sizeof(DCB);

	log_debug(log, "set comm configuration for device %s.", device);
	if (!setCommConfiguration(device, pdata, &port)) {
		rssconSetLastError(rsscon, RSSCON_ERROR_SETUPDEVICE);
		return false;
	}

	log_debug(log, "set the comm state for the port handler %d.", pdata->portHandle);
	if (!setCommState(device, pdata, &port)) {
		rssconSetLastError(rsscon, RSSCON_ERROR_SETUPDEVICE);
		return false;
	}

	log_debug(log, "set the handshake for the port handler %d.", pdata->portHandle);
	if (!handshakeOff(pdata)) {
		rssconSetLastError(rsscon, RSSCON_ERROR_SETUPDEVICE);
		return false;
	}

	log_debug(log, "set the timeout blocking for the port handler %d.", pdata->portHandle);
	if (!readTimeoutBlocking(pdata)) {
		rssconSetLastError(rsscon, RSSCON_ERROR_SETUPDEVICE);
		return false;
	}

	return true;
}