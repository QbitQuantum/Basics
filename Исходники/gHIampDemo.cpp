//Starts the thread that does the data acquisition.
void StartAcquisition()
{
	int numChannels = NUMBER_OF_CHANNELS + (int) ENABLE_TRIGGER;

	_isRunning = true;
	_bufferOverrun = false;

	//give main process (the data processing thread) high priority
	HANDLE hProcess = GetCurrentProcess();
	SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);

	//initialize application data buffer to the specified number of seconds
	_buffer.Initialize(BUFFER_SIZE_SECONDS * SAMPLE_RATE_HZ * numChannels);

	//reset event
	_dataAcquisitionStopped.ResetEvent();

	//create data acquisition thread with high priority
	_dataAcquisitionThread = AfxBeginThread(DoAcquisition, NULL, THREAD_PRIORITY_TIME_CRITICAL,0, CREATE_SUSPENDED);
	_dataAcquisitionThread->ResumeThread();
}