/*
	The following block is copied from the Java source code. It documents the counters array.

	 * @param counters the results are returned in this array.
	 * <ol>
	 * <li>working set in bytes for this process
	 * <li>peak working set in bytes for this process
	 * <li>elapsed time in milliseconds
	 * <li>user time in milliseconds
	 * <li>kernel time in milliseconds
	 * <li>page faults for the process
	 * <li>commit charge total in bytes (working set for the entire machine). On some 
	 * machines we have problems getting this value so we return -1 in that case.
	 * <li>number of GDI objects in the process
	 * <li>number of USER objects in the process
	 * <li>number of open handles in the process. returns -1 if this information is not available
	 * <li>Number of read operations
	 * <li>Number of write operations
	 * <li>Number of bytes read
	 * <li>Number of bytes written
	 * </ol>

*/
JNIEXPORT jboolean JNICALL Java_org_eclipse_perfmsr_core_PerformanceMonitor_nativeGetPerformanceCounters
  (JNIEnv * jniEnv, jclass jniClass, jlongArray counters)
{
	FILETIME creationTime, exitTime, kernelTime, userTime, systemTime;
	ULARGE_INTEGER uliCreation, uliSystem, uliKernel, uliUser;
	ULONGLONG diff;
	IO_COUNTERS ioCounters;

	jboolean result = TRUE;
	jsize len = (*jniEnv)->GetArrayLength(jniEnv, counters);
	jlong *body = (*jniEnv)->GetLongArrayElements(jniEnv, counters, 0);
	HANDLE me = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS memCounters;
	DWORD cb = sizeof(PROCESS_MEMORY_COUNTERS);
	BOOL rc = GetProcessMemoryInfo(me, &memCounters, cb);
	if (rc != 0)
	{
		body[0] = memCounters.WorkingSetSize;
		body[1] = memCounters.PeakWorkingSetSize;
		body[5] = memCounters.PageFaultCount;
	}
	else
	{
		handleSystemError(jniEnv);
		return FALSE;
	}

	if (!GetProcessTimes(me, &creationTime, &exitTime, &kernelTime, &userTime))
	{
		handleSystemError(jniEnv);
		return FALSE;
	}
	GetSystemTimeAsFileTime(&systemTime);

	memcpy(&uliCreation, &creationTime, sizeof(uliCreation));  
	memcpy(&uliSystem, &systemTime, sizeof(uliSystem));
	memcpy(&uliKernel, &kernelTime, sizeof(uliSystem));
	memcpy(&uliUser, &userTime, sizeof(ULARGE_INTEGER));
	diff = uliSystem.QuadPart - uliCreation.QuadPart;
	body[2] = diff / 10000;
	body[3] = uliUser.QuadPart / 10000;
	body[4] = uliKernel.QuadPart / 10000;
	body[6] = getTotalCommitted(jniEnv);

	body[7] = GetGuiResources(me, GR_GDIOBJECTS);
	body[8] = GetGuiResources(me, GR_USEROBJECTS);
	body[9] = getHandleCount(jniEnv, me);

	if (!GetProcessIoCounters(me, &ioCounters))
	{
		handleSystemError(jniEnv);
		return FALSE;
	}
	body[10] = ioCounters.ReadOperationCount;
	body[11] = ioCounters.WriteOperationCount;
	body[12] = ioCounters.ReadTransferCount;
	body[13] = ioCounters.WriteTransferCount;

	(*jniEnv)->ReleaseLongArrayElements(jniEnv, counters, body, 0);

	return result;
}