int transport_check_fds(rdpTransport* transport)
{
	int status;
	int recv_status;
	wStream* received;

	if (!transport)
		return -1;

#ifdef _WIN32
	WSAResetEvent(transport->TcpIn->event);
#endif
	ResetEvent(transport->ReceiveEvent);

	/**
	 * Loop through and read all available PDUs.  Since multiple
	 * PDUs can exist, it's important to deliver them all before
	 * returning.  Otherwise we run the risk of having a thread
	 * wait for a socket to get signaled that data is available
	 * (which may never happen).
	 */
	for (;;)
	{
		/**
		 * Note: transport_read_pdu tries to read one PDU from
		 * the transport layer.
		 * The ReceiveBuffer might have a position > 0 in case of a non blocking
		 * transport. If transport_read_pdu returns 0 the pdu couldn't be read at
		 * this point.
		 * Note that transport->ReceiveBuffer is replaced after each iteration
		 * of this loop with a fresh stream instance from a pool.
		 */
		if ((status = transport_read_pdu(transport, transport->ReceiveBuffer)) <= 0)
		{
			return status;
		}

		received = transport->ReceiveBuffer;
		transport->ReceiveBuffer = StreamPool_Take(transport->ReceivePool, 0);
		/**
		 * status:
		 * 	-1: error
		 * 	 0: success
		 * 	 1: redirection
		 */
		recv_status = transport->ReceiveCallback(transport, received, transport->ReceiveExtra);
		Stream_Release(received);

		/* session redirection or activation */
		if (recv_status == 1 || recv_status == 2)
		{
			return recv_status;
		}

		if (recv_status < 0)
			return -1;
	}

	return 0;
}