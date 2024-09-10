void Mixer::remoteTryConnect(const ::agh::CallParameters& params, const ::Ice::Identity& ident, const ::Ice::Current& curr) {
	stringstream a;
	LOG4CXX_DEBUG(logger, string("Mixer::remoteTryConnect()"));
	masterCallbackPrx = IMasterCallbackPrx::uncheckedCast(curr.con->createProxy(ident));

	if (localAddr) {
		delete localAddr;
	}
	if (remoteAddr) {
		delete remoteAddr;
	}

	IPV4Address *tmpAddr = new IPV4Address(getRemoteAddressFromConnection(curr.con));
	TerminalInfo *info = new TerminalInfo;
	info->address = *tmpAddr;
	info->rtpPort = params.masterRtpPort;
	info->outgoingCodec = params.outgoingCodec.id;
	info->incomingCodec = params.incomingCodec.id;
	info->transport = NULL;
	info->readedSize = 0;
	info->buf = NULL;
	remoteHostsM[tmpAddr->getHostname()] = info;
	a << "Mixer::remoteTryConnect() conf received, remote addr: " << tmpAddr << " port: " << params.masterRtpPort;
	LOG4CXX_DEBUG(logger, a.str());

	changeState(States::PASSIVE_CONNECTED);

	// inform remote site
	LOG4CXX_DEBUG(logger, string("Mixer::remoteTryConnect() sending ACK..."));
	CallParametersResponse response;
	response.slaveRtpPort = localRTPPort;

	// Response in new thread
	WorkerThread* tmpThread = new WorkerThread(this, response);
	tmpThread->start();
	LOG4CXX_DEBUG(logger, string("Mixer::remoteTryConnect() ACK has been sent"));
}