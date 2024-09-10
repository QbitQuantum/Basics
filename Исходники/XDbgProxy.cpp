void XDbgProxy::CreateRemoteThread(ApiCallPacket& inPkt)
{
	ApiReturnPakcet outPkt;
	ULONG pid;
	if (!GetNamedPipeClientProcessId(_hApiPipe, &pid)) {
		assert(false);
		outPkt.CreateRemoteThread.result = NULL;
		outPkt.lastError = ERROR_INVALID_PARAMETER;
		sendApiReturn(outPkt);
		return;
	}

	HANDLE hProc = ::OpenProcess(PROCESS_DUP_HANDLE, FALSE, pid);
	if (hProc == NULL) {
		assert(false);
		outPkt.CreateRemoteThread.result = NULL;
		outPkt.lastError = ERROR_INVALID_PARAMETER;
		sendApiReturn(outPkt);
		return;
	}

	HANDLE hThread = ::CreateThread(inPkt.CreateRemoteThread.lpThreadAttributes,
		inPkt.CreateRemoteThread.dwStackSize, inPkt.CreateRemoteThread.lpStartAddress,
		inPkt.CreateRemoteThread.lpParameter, inPkt.CreateRemoteThread.dwCreationFlags,
		&outPkt.CreateRemoteThread.threadId);

	if (hThread == NULL) {
		outPkt.lastError = GetLastError();
		outPkt.CreateRemoteThread.result = NULL;
	} else {
		if (!DuplicateHandle(GetCurrentProcess(), hThread, hProc, &outPkt.CreateRemoteThread.result,
			0, FALSE, DUPLICATE_SAME_ACCESS)) {

			assert(false);
			outPkt.CreateRemoteThread.result = NULL;
			outPkt.lastError = ERROR_INVALID_PARAMETER;
		}

		CloseHandle(hThread);
	}

	CloseHandle(hProc);
	sendApiReturn(outPkt);
}