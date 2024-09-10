void CSyncEngineWrap::SendWindowEvent(TInt aEvent)
	{
	// Create a window server event
	RWsSession wsSession;
	TWsEvent event;

	if (wsSession.Connect() == KErrNone)
		{
		// Set event data. eventType.data = KData;
		event.SetType(EEventUser + aEvent); // set event type
		event.SetTimeNow(); // set the event time
		event.SetHandle(wsSession.WsHandle()); // set window server handle

		// Send the created event
		wsSession.SendEventToAllWindowGroups(event);
		}
	}