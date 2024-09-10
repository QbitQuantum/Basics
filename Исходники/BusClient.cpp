void BusClient::SendRequest(MojServiceRequest::ReplySignal::SlotRef handler, const MojChar* service,
		const MojChar* method, const MojObject& payload, MojUInt32 numReplies)
{
	MojRefCountedPtr<MojServiceRequest> req = CreateRequest();

	MojErr err = req->send(handler, service, method, payload, numReplies);
	ErrorToException(err);
}