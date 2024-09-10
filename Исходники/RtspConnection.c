/* Perform RTSP Handshake with the streaming server machine as part of the connection process */
int performRtspHandshake(IP_ADDRESS addr, PSTREAM_CONFIGURATION streamConfigPtr) {
	struct in_addr inaddr;

	// Initialize global state
	remoteAddr = addr;
    memcpy(&inaddr, &addr, sizeof(addr));
	sprintf(rtspTargetUrl, "rtsp://%s", inet_ntoa(inaddr));
	currentSeqNumber = 1;
	hasSessionId = 0;
    
    if (serverMajorVersion == 3) {
        rtspClientVersion = 10;
    }
    else {
        rtspClientVersion = 11;
    }

	{
		RTSP_MESSAGE response;

		if (!requestOptions(&response)) {
			Limelog("RTSP OPTIONS request failed\n");
			return -1;
		}

		if (response.message.response.statusCode != 200) {
			Limelog("RTSP OPTIONS request failed: %d\n",
				response.message.response.statusCode);
			return -1;
		}

		freeMessage(&response);
	}

	{
		RTSP_MESSAGE response;

		if (!requestDescribe(&response)) {
			Limelog("RTSP DESCRIBE request failed\n");
			return -1;
		}

		if (response.message.response.statusCode != 200) {
			Limelog("RTSP DESCRIBE request failed: %d\n",
				response.message.response.statusCode);
			return -1;
		}

		freeMessage(&response);
	}

	{
		RTSP_MESSAGE response;
		char* sessionId;

		if (!setupStream(&response, "streamid=audio")) {
			Limelog("RTSP SETUP streamid=audio request failed\n");
			return -1;
		}

		if (response.message.response.statusCode != 200) {
			Limelog("RTSP SETUP streamid=audio request failed: %d\n",
				response.message.response.statusCode);
			return -1;
		}

		sessionId = getOptionContent(response.options, "Session");
		if (sessionId == NULL) {
			Limelog("RTSP SETUP streamid=audio is missing session attribute");
			return -1;
		}

		strcpy(sessionIdString, sessionId);
		hasSessionId = 1;

		freeMessage(&response);
	}

	{
		RTSP_MESSAGE response;

		if (!setupStream(&response, "streamid=video")) {
			Limelog("RTSP SETUP streamid=video request failed\n");
			return -1;
		}

		if (response.message.response.statusCode != 200) {
			Limelog("RTSP SETUP streamid=video request failed: %d\n",
				response.message.response.statusCode);
			return -1;
		}

		freeMessage(&response);
	}

	{
		RTSP_MESSAGE response;

		if (!sendVideoAnnounce(&response, streamConfigPtr)) {
			Limelog("RTSP ANNOUNCE request failed\n");
			return -1;
		}

		if (response.message.response.statusCode != 200) {
			Limelog("RTSP ANNOUNCE request failed: %d\n",
				response.message.response.statusCode);
			return -1;
		}

		freeMessage(&response);
	}

	{
		RTSP_MESSAGE response;

		if (!playStream(&response, "streamid=video")) {
			Limelog("RTSP PLAY streamid=video request failed\n");
			return -1;
		}

		if (response.message.response.statusCode != 200) {
			Limelog("RTSP PLAY streamid=video failed: %d\n",
				response.message.response.statusCode);
			return -1;
		}

		freeMessage(&response);
	}

	{
		RTSP_MESSAGE response;

		if (!playStream(&response, "streamid=audio")) {
			Limelog("RTSP PLAY streamid=audio request failed\n");
			return -1;
		}

		if (response.message.response.statusCode != 200) {
			Limelog("RTSP PLAY streamid=audio failed: %d\n",
				response.message.response.statusCode);
			return -1;
		}

		freeMessage(&response);
	}

	return 0;
}