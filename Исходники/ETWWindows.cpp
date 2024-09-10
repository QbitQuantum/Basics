bool ETW::Stop()
{
	if (isActive)
	{
		ULONG controlTraceResult = ControlTrace(openedHandle, KERNEL_LOGGER_NAME, sessionProperties, EVENT_TRACE_CONTROL_STOP);

		// ERROR_CTX_CLOSE_PENDING(7007L): The call was successful. The ProcessTrace function will stop after it has processed all real-time events in its buffers (it will not receive any new events).
		// ERROR_BUSY(170L): Prior to Windows Vista, you cannot close the trace until the ProcessTrace function completes.
		// ERROR_INVALID_HANDLE(6L): One of the following is true: TraceHandle is NULL. TraceHandle is INVALID_HANDLE_VALUE.
		ULONG closeTraceStatus = CloseTrace(openedHandle);

		// Wait for ProcessThread to finish
		WaitForSingleObject(processThreadHandle, INFINITE);
		BOOL wasThreadClosed = CloseHandle(processThreadHandle);

		isActive = false;

		return wasThreadClosed && closeTraceStatus == ERROR_SUCCESS && controlTraceResult == ERROR_SUCCESS;
	}

	return false;
}