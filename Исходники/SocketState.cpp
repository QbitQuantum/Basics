void SocketStateConnecting::update()
{	
	float timeout = socket->getConnectTimeout();
	if (timeout > 0 && (time(0) - start) >= timeout) {
		// Note: after setState, this object is released!
		Socket *s = socket;
		s->setState(sDisconnected);
		s->shutdown();
		return;
	}

	if (socket->canWrite()) {
		if (socket->checkConnected()) {
			socket->onConnect();
		} else {
			Socket *s = socket;
			s->setState(sDisconnected);
			s->emitError();
		}
	}
}