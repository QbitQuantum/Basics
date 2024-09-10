int appCaptureStackTrace(address_t* buffer, int maxDepth, int framesToSkip)
{
	return RtlCaptureStackBackTrace(framesToSkip, maxDepth, (void**)buffer, NULL);
}