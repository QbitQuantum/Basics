static void o_Reuse(PKOVL_HANDLE_INTERNAL overlapped)
{
	if (!overlapped->Overlapped.hEvent)
		overlapped->Overlapped.hEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
	else
		ResetEvent(overlapped->Overlapped.hEvent);
}