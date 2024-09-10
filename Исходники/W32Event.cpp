void Event::Reset()
{
	if (wsaEvent == NULL)
		KNET_LOG(LogError, "Event::Reset called on a null event!");
	else
		WSAResetEvent(wsaEvent);
}