    virtual unsigned ThreadHandlerProc(void)
    {
	CHAR boxName[50];
	DWORD err, dwWritten;
	IPCMsg msg;

	wsprintf(boxName, "ExpectInjector_pid%d", GetCurrentProcessId());

	// Create the shared memory IPC transfer mechanism by name
	// (a mailbox).
	ConsoleDebuggerIPC = 
		new CMclMailbox(IPC_NUMSLOTS, IPC_SLOTSIZE, boxName);

	// Check status.
	err = ConsoleDebuggerIPC->Status();
	if (err != NO_ERROR && err != ERROR_ALREADY_EXISTS) {
	    OutputDebugString(GetSysMsg(err));
	    delete ConsoleDebuggerIPC;
	    return 0x666;
	}

	OutputDebugString("Expect's injector DLL loaded and ready.\n");

	// forever loop receiving messages over IPC.
	while (ConsoleDebuggerIPC->GetAlertable(&msg, interrupt)) {
	    switch (msg.type) {
	    case CTRL_EVENT:
		// Generate a Ctrl+C or Ctrl+Break to cause the equivalent
		// of a SIGINT into this process.
		GenerateConsoleCtrlEvent(msg.event, 0);
		break;
	    case IRECORD:
		// Stuff it into this console as if it had been entered
		// by the user.
#ifdef IPC_MAXRECORDS
		// If IPC_MAXRECORDS is defined, we have grouped key events.
		WriteConsoleInput(console, msg.irecord, msg.event,
				  &dwWritten);
#else
		WriteConsoleInput(console, &msg.irecord, 1, &dwWritten);
#endif
		break;
	    }
	}
	delete ConsoleDebuggerIPC;
	return 0;
    }