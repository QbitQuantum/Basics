// Construct a faked event, storing the supplied event parameters into the supplied empty event data buffer.
EXPORT_C TLoopbackCommandEvent::TLoopbackCommandEvent(const TDesC8& aHCICommandPacket, TDes8& aEventData)
	: THCIEventBase(ELoopbackCommandEvent, aEventData.Length(), aEventData)
	{
	
	PutString(aHCICommandPacket, aEventData);
	iEventData.Set(aEventData);
	}