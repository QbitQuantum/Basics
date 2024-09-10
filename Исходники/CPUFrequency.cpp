// This thread controls the CPU frequency measurements.
void CCPUFrequencyMonitor::Sample()
{
	// Get the actual number of CPUs, in case numCPUs_ was trimmed.
	// Otherwise CallNtPowerInformation won't return any data.
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	DWORD actualNumberCPUs = systemInfo.dwNumberOfProcessors;

	// Ask Windows what frequency it thinks the CPUs are running at.
	std::vector<PROCESSOR_POWER_INFORMATION> processorInfo(actualNumberCPUs);
	NTSTATUS powerStatus = CallNtPowerInformation(ProcessorInformation, nullptr,
		0, &processorInfo[0],
		sizeof(processorInfo[0]) * actualNumberCPUs);

	ULONG maxPromisedMHz = 0;
	// Most common failure result is:
	// #define STATUS_BUFFER_TOO_SMALL          ((NTSTATUS)0xC0000023L)
	if (powerStatus >= 0)
	{
		for (DWORD i = 0; i < actualNumberCPUs; ++i)
		{
			maxPromisedMHz = std::max(maxPromisedMHz, processorInfo[i].CurrentMhz);
		}
	}

	// Release all of the per-CPU measurement threads. This is not
	// actually guaranteed to wake up all of the threads - one thread
	// could 'absorb' all of the semaphores, but in practice this works
	// very well. Releasing numCPUs_ different semaphores would guarantee
	// that all of the individual threads would run, but would require
	// this thread to run more code (releasing individual semaphores) which
	// might cause more worrisome interference.
	ReleaseSemaphore(workStartSemaphore_, numCPUs_, nullptr);

	// Sleep a little while to give the calculation threads time to finish
	// without this thread interfering.
	Sleep(10);

	// Make sure the CPU frequency measurements are finished.
	for (unsigned i = 0; i < numCPUs_; ++i)
		WaitForSingleObject(resultsDoneSemaphore_, INFINITE);

	// Find the maximum measured frequencies.
	float maxActualFreq = threads_[0].frequency;
	for (DWORD i = 1; i < numCPUs_; ++i)
	{
		maxActualFreq = std::max(maxActualFreq, threads_[i].frequency);
	}

	float freqPercentage = maxActualFreq * 100.f / maxPromisedMHz;
	PCWSTR pStatus = L"Normal";
	if (freqPercentage < 75)
		pStatus = L"Probably modest thermal throttling";
	if (freqPercentage < 50)
		pStatus = L"Probably significant thermal throttling";
	ETWMarkCPUThrottling(startFrequency_, maxActualFreq, static_cast<float>(maxPromisedMHz), freqPercentage, pStatus);
}