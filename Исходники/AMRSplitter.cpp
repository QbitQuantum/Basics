// vlakno na output
DWORD CAMROutputPin::ThreadProc()
{
	while (true) {
		DWORD cmd = GetRequest();
		switch (cmd) {
			case CMD_EXIT:		Reply(0); return 0; break;
			case CMD_STOP:
				{
					Reply(0); 
				}
				break;
			case CMD_RUN:
				{
					Reply(0);
					if (!IsConnected()) {
						break;
					}

					// deliver packets
					DWORD	cmd2;
					BOOL	is_first = true;
					DataPacketAMR	*packet;
					HRESULT	hr;

					do {
						if (ev_abort.Check()) {
							break;
						}
						hr = NOERROR;
					
						HANDLE	events[] = { ev_can_read, ev_abort};
						DWORD	ret = WaitForMultipleObjects(2, events, FALSE, 10);

						if (ret == WAIT_OBJECT_0) {
							// look for new packet in queue
							{
								CAutoLock	lck(&lock_queue);
								packet = queue.RemoveHead();
								if (queue.IsEmpty()) {
									ev_can_read.Reset();
								}

								// allow buffering
								if (GetBufferTime_MS() < buffer_time_ms) {
									ev_can_write.Set();
								}
							}

							// bud dorucime End Of Stream, alebo packet
							if (packet->type == DataPacketAMR::PACKET_TYPE_EOS) {
								DeliverEndOfStream();
							} else if (packet->type == DataPacketAMR::PACKET_TYPE_NEW_SEGMENT) {
								hr = DeliverNewSegment(packet->rtStart, packet->rtStop, packet->rate);
							} else if (packet->type == DataPacketAMR::PACKET_TYPE_DATA) {
								hr = DeliverDataPacketAMR(*packet);
							}					

							delete packet;

							if (FAILED(hr)) {
								break;
							}
						}
					} while (!CheckRequest(&cmd2));
				}
				break;
			default:
				Reply(E_UNEXPECTED); 
				break;
		}
	}
	return 0;
}