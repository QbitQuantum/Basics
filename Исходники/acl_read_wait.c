int acl_read_wait(ACL_SOCKET fd, int timeout)
{
	const char *myname = "acl_read_wait";
	OVERLAPPED *overlapped, *lpOverlapped;
	DWORD recvBytes;
	BOOL isSuccess;
	ACL_SOCKET fd2;
	DWORD bytesTransferred = 0;
	DWORD delay = timeout * 1000;
	HANDLE h2;

	if (__handle == NULL)
		__handle = CreateIoCompletionPort(INVALID_HANDLE_VALUE,
				NULL, 0, 0);
	if (__handle == NULL) {
		acl_msg_error("CreateIoCompletionPort: %s",
			acl_last_serror());
		return -1;
	}

	overlapped = acl_mycalloc(1, sizeof(OVERLAPPED));

	h2  = CreateIoCompletionPort((HANDLE) fd, __handle,
		(DWORD) overlapped, 0);
	if (h2 == NULL)
		acl_myfree(overlapped);
	else if (h2 != __handle) {
		acl_msg_error("invalid h2 by CreateIoCompletionPort: %s",
			acl_last_serror());
		CloseHandle(h2);
		return -1;
	}

	if (ReadFile((HANDLE) fd, NULL, 0, &recvBytes, overlapped) == FALSE
		&& acl_last_error() != ERROR_IO_PENDING)
	{
		acl_msg_warn("%s(%d): ReadFile error(%s)",
			myname, __LINE__, acl_last_serror());
		return -1;
	}

	delay = 6000;

	while (1)
	{
		isSuccess = GetQueuedCompletionStatus(__handle,
				&bytesTransferred,
				(DWORD*) &fd2,
				(OVERLAPPED**) &lpOverlapped,
				delay);
		if (lpOverlapped == NULL)
			break;

		if (HasOverlappedIoCompleted(lpOverlapped))
			acl_myfree(lpOverlapped);

		if (isSuccess)
			return 0;
	}

	acl_msg_warn("timeout error: %s", acl_last_serror());
	return -1;
}