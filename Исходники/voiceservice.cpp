static VOID CALLBACK ClearOldVoiceCalls(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	DWORD now = GetTickCount();
	BOOL refresh = FALSE;
	for(int i = calls.getCount() - 1; i >= 0; --i)
	{
		VoiceCall *call = &calls[i];

		if (call->state == VOICE_STATE_ENDED && call->end_time + TIME_TO_SHOW_ENDED_CALL < now)
		{
			calls.remove(i);
			refresh = TRUE;
		}
	}

	if (refresh && hwnd_frame != NULL)
		PostMessage(hwnd_frame, WMU_REFRESH, 0, 0);
}