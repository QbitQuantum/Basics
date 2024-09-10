static BOOL audin_server_open(audin_server_context* context)
{
	audin_server* audin = (audin_server*) context;

	if (!audin->thread)
	{
		PULONG pSessionId = NULL;
		DWORD BytesReturned = 0;

		audin->SessionId = WTS_CURRENT_SESSION;

		if (WTSQuerySessionInformationA(context->vcm, WTS_CURRENT_SESSION,
				WTSSessionId, (LPSTR*) &pSessionId, &BytesReturned))
		{
			audin->SessionId = (DWORD) *pSessionId;
			WTSFreeMemory(pSessionId);
		}

		audin->audin_channel = WTSVirtualChannelOpenEx(audin->SessionId,
				"AUDIO_INPUT", WTS_CHANNEL_OPTION_DYNAMIC);

		if (!audin->audin_channel)
			return FALSE;

		audin->stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		audin->thread = CreateThread(NULL, 0,
				(LPTHREAD_START_ROUTINE) audin_server_thread_func, (void*) audin, 0, NULL);

		return TRUE;
	}

	return FALSE;
}