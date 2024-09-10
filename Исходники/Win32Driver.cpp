void Win32MidiDriver::start() {
	HANDLE processingThreadHandle = (HANDLE)_beginthread(&messageLoop, 16384, NULL);
	SetThreadPriority(processingThreadHandle, THREAD_PRIORITY_TIME_CRITICAL);
}