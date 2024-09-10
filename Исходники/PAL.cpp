void ThreadPool::AssociateHandle(native_handle_t h, LPFN_COMPLETION_PROC fn)
{
	panic_if(queue == nullptr, "ThreadPool is not initialized");
	if (startSockets.syncCompletion) {
		auto success = SetFileCompletionNotificationModes(
			(HANDLE)h, FILE_SKIP_COMPLETION_PORT_ON_SUCCESS);
		panic_if(!success, "FILE_SKIP_COMPLETION_PORT_ON_SUCCESS");
	}
	queue->AssociateHandle((HANDLE)h, fn);
}