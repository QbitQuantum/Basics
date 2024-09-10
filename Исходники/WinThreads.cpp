IEventSignal *WinThreader::MakeEventSignal()
{
	HANDLE event = CreateEventA(NULL, FALSE, FALSE, NULL);

	if (!event)
		return NULL;

	WinEvent *pEvent = new WinEvent(event);

	return pEvent;
}