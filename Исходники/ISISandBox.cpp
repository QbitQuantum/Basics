int ISISandBoxRemoveProtectProcess(DWORD aProcessId)
{
	int errCode = ERROR_SUCCESS;
	HANDLE driverPort = NULL;

	__try
	{
		// 测试连接
		HRESULT ret = FilterConnectCommunicationPort(ISISandBoxPortName, 0, NULL, 0, NULL, &driverPort);
		if (IS_ERROR(ret))
		{
			errCode = ERROR_NOT_CONNECTED;
			__leave;
		}

		MESSAGE_PROTECT_PROCESS_SEND message;
		message.Message.MessageType = MESSAGE_REMOVE_PROTECT_PROCESS;
		message.Message.ProcessId = (HANDLE)aProcessId;

		DWORD replyLength = 0;
		MESSAGE_REPLY reply;

		ret = FilterSendMessage(driverPort, (PFILTER_MESSAGE_HEADER)&message, sizeof(MESSAGE_PROTECT_PATH_SEND), (PVOID)&reply, sizeof(MESSAGE_REPLY), &replyLength);
		if (ret != S_OK)
		{
			errCode = GetLastError();
			__leave;
		}

		if (reply.MessageType != MESSAGE_INSERT_PROTECT_PROCESS && reply.status != 0)
		{
			errCode = ERROR_NOT_SUPPORTED;
			__leave;
		}
	}
	__finally
	{
		CloseHandle(driverPort);
		driverPort = NULL;
	}

	return ERROR_SUCCESS;
}