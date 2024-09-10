void ClientConnection::_threadEntry() {
	try {
		while (_continueRunning) {
			auto txn = _getTransaction();

			auto result = _db->processTransaction(txn);

			_sendResult(result);

		}
	} catch(std::exception &e) {
		if (_continueRunning) {
			Logf(kLogLevelDebug, e.what());
		}
	}

	// this thread needs to finish before the client can destruct. Kill the client from the service thread.
	_service.post([=]() { _db->removeClient(shared_from_this()); });
}