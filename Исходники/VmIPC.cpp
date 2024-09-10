DWORD WINAPI PipeThreadMonitor(LPVOID Arg)
{
	IPCPacket packet;

	for (;;)
	{
		// Wait for the client to connect
		if (!ConnectNamedPipe(g_Pipe, nullptr))
		{
			printf("An error occurred while waiting for a client connection\n");
			return 1;
		}

		for (bool runloop = true; runloop;)
		{
			// Wait for a client message to be sent
			if (!ReadFromPipe(&packet))
			{
				printf("Failed to read from client connection\n");
				
				runloop = false;
				break;
			}

			// Handle the message here
			switch (packet.MessageType)
			{
			case VM_CLIENT_READMEM_CMD:
				VmHandleReadMem(&packet);
				break;

			case VM_CLIENT_WRITEMEM_CMD:
				VmHandleWriteMem(&packet);
				break;

			case VM_CLIENT_SHUTDOWN_CMD:
				printf("GOT A SHUTDOWN MESSAGE TYPE\n");

				// Exit the loop
				runloop = false;
				break;

			default:
				printf("GOT AN UNKNOWN MESSAGE TYPE\n");

				packet.Status = 0;
				break;
			}

			// Send the resulting packet
			if (!WriteToPipe(&packet))
				return 1;
		}

		// Disconnect the client
		DisconnectNamedPipe(g_Pipe);
	}

	return 0;
}