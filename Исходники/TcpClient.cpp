void TCPClient::onRelayConnectionConnect(void* sender)
{		
	TraceL << "onRelayConnectionConnect" << endl;	
	
	auto conn =reinterpret_cast<net::Socket*>(sender);
	conn->Connect -= sdelegate(this, &TCPClient::onRelayConnectionConnect);
	auto req = reinterpret_cast<RelayConnectionBinding*>(conn->opaque);
	assert(connections().has(req->peerAddress));

	// TODO: How to get peerAddress here?
	//net::TCPSocket& socket = _connections.get(peerAddress, conn);

	auto transaction = createTransaction(connections().get(req->peerAddress));
	transaction->request().setClass(stun::Message::Request);
	transaction->request().setMethod(stun::Message::ConnectionBind);

	auto connAttr = new stun::ConnectionID;
	connAttr->setValue(req->connectionID);
	transaction->request().add(connAttr);
		
	//assert(transaction->socket() == &conn);
	sendAuthenticatedTransaction(transaction);
}