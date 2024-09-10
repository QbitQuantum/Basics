void* SpeechThreed(void* args)
{
	void** args_ = (void**)args;
	KinectTool* self = (KinectTool*)(args_[0]);
	Input* input = (Input*)(args_[1]);
	free(args);

	printf("Thread started.");

	for(;;)
	{
		/* Speech Start */
		hEvents[0] = self->_reader->m_hSpeechEvent;

		// Check to see if we have either a message (by passing in QS_ALLINPUT)
		// Or a speech event (hEvents)
		DWORD dwEvent = MsgWaitForMultipleObjectsEx(eventCount, hEvents, INFINITE, QS_ALLINPUT, MWMO_INPUTAVAILABLE);

		// Check if this is an event we're waiting on and not a timeout or message
		if (WAIT_OBJECT_0 == dwEvent)
		{
			self->_reader->ProcessSpeech(input);
		}
	/*
	if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // If a dialog message will be taken care of by the dialog proc
            if ((hWndApp != NULL) && IsDialogMessageW(hWndApp, &msg))
            {
                continue;
            }

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
		*/
	/* Speech end */
	}

	return NULL;
}