//Unregisters the hotkeys and destroys the message handling thread
void cleanup()
{
	//Check that there is a spawned thread to cleanup.
	if (threadHandle != NULL)
	{
		//Flag that we are cleaning up.
		cleaningUp = TRUE;
		
		//Wait for the message handling thread to unregister the hotkeys.
		WaitForSingleObject(threadHandle, INFINITE);
		
		//Close the thread's handle.
		CloseHandle(threadHandle);
		threadHandle = NULL;
	}

    if (msgWindowHandle != NULL) {
        WTSUnRegisterSessionNotification(msgWindowHandle);
        SendMessage(msgWindowHandle, WM_CLOSE, 0, 0);
    }
}