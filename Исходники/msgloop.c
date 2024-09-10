static void msgloop_loop(void * vqlink)
{
	WSAEVENT hReadEvent;
	SOCKET rx_socket = vqp_link_rx_socket((vqp_link_t) vqlink);

	s_fLoopStarted = TRUE;

	hReadEvent = WSACreateEvent();
	WSAEventSelect(rx_socket, hReadEvent, FD_READ);

	while(!Miranda_Terminated() && !s_fStopLoop) {
		DWORD nEvent = WSAWaitForMultipleEvents(
				1, &hReadEvent, FALSE, WSA_INFINITE, TRUE);

		if(nEvent==WSA_WAIT_EVENT_0) {
			vqp_msg_t msg;

			WSAResetEvent(hReadEvent);
	
			if(!vqp_link_recv((vqp_link_t) vqlink, &msg)) {
				QueueUserAPC(
					s_lpfnMsgHandleApc,
					s_hMainThread, (ULONG_PTR)msg);
			}
		}
	}

	WSACloseEvent(hReadEvent);

	/* wait for pending user APC */
	while(SleepEx(10, TRUE) == WAIT_IO_COMPLETION) /* nothing */;

	/* signal that we've finished */
	SetEvent(s_hStopWaitEvent);
}