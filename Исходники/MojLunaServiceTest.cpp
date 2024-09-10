	MojErr sendEcho(const MojChar* json, const MojObject& expectedResponse, const MojChar* method)
	{
		MojRefCountedPtr<EchoResponseHdlr> handler(new EchoResponseHdlr(expectedResponse, ++m_pendingResponseCount));
		MojAllocCheck(handler.get());

		MojRefCountedPtr<MojServiceRequest> req;
		MojErr err = m_service.createRequest(req);
		MojTestErrCheck(err);

		MojObject payload;
		err = payload.fromJson(json);
		MojTestErrCheck(err);
		err = req->send(handler->m_slot, ServiceName, method, payload);
		MojTestErrCheck(err);

		return MojErrNone;
	}