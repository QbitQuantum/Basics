void cancel(WatchData &watch){
	if (CancelIo(watch.dir_handle) == 0){
		std::cerr << "lfw Error: cancelling watch: "
			<< get_error_msg(GetLastError()) << std::endl;
	}
	//Give the watcher time to get the cancellation event and set the event
	MsgWaitForMultipleObjectsEx(0, nullptr, 0, QS_ALLINPUT, MWMO_ALERTABLE);
	DWORD status = WaitForSingleObject(watch.overlapped.hEvent, INFINITE);
	if (status == WAIT_FAILED){
		std::cerr << "lfw Error: failed to wait for cancellation: "
			<< get_error_msg(GetLastError()) << std::endl;
	}
	CloseHandle(watch.dir_handle);
	CloseHandle(watch.overlapped.hEvent);
}