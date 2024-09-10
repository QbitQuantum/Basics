struct wpa_ctrl * wpa_ctrl_open(const char *ctrl_path)
{
	struct wpa_ctrl *ctrl;
	DWORD mode;
	TCHAR name[256];
	int i, ret;

	ctrl = os_malloc(sizeof(*ctrl));
	if (ctrl == NULL)
		return NULL;
	os_memset(ctrl, 0, sizeof(*ctrl));

#ifdef UNICODE
	if (ctrl_path == NULL)
		ret = _snwprintf(name, 256, NAMED_PIPE_PREFIX);
	else
		ret = _snwprintf(name, 256, NAMED_PIPE_PREFIX TEXT("-%S"),
				 ctrl_path);
#else /* UNICODE */
	if (ctrl_path == NULL)
		ret = os_snprintf(name, 256, NAMED_PIPE_PREFIX);
	else
		ret = os_snprintf(name, 256, NAMED_PIPE_PREFIX "-%s",
				  ctrl_path);
#endif /* UNICODE */
	if (os_snprintf_error(256, ret)) {
		os_free(ctrl);
		return NULL;
	}

	for (i = 0; i < 10; i++) {
		ctrl->pipe = CreateFile(name, GENERIC_READ | GENERIC_WRITE, 0,
					NULL, OPEN_EXISTING, 0, NULL);
		/*
		 * Current named pipe server side in wpa_supplicant is
		 * re-opening the pipe for new clients only after the previous
		 * one is taken into use. This leaves a small window for race
		 * conditions when two connections are being opened at almost
		 * the same time. Retry if that was the case.
		 */
		if (ctrl->pipe != INVALID_HANDLE_VALUE ||
		    GetLastError() != ERROR_PIPE_BUSY)
			break;
		WaitNamedPipe(name, 1000);
	}
	if (ctrl->pipe == INVALID_HANDLE_VALUE) {
		os_free(ctrl);
		return NULL;
	}

	mode = PIPE_READMODE_MESSAGE;
	if (!SetNamedPipeHandleState(ctrl->pipe, &mode, NULL, NULL)) {
		CloseHandle(ctrl->pipe);
		os_free(ctrl);
		return NULL;
	}

	return ctrl;
}