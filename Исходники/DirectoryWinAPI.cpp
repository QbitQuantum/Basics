bool DirectoryWinAPI::setWatch(const std::string& path, ICallbackBase<void>* cb)
{
	if(callbacks.size() > MAXIMUM_WAIT_OBJECTS)
	{
		LOGERROR("Too many objects being watched", "setWatch");
	}

	HANDLE watchHandle = FindFirstChangeNotification(path.c_str(), TRUE, FILE_NOTIFY_CHANGE_LAST_WRITE);
	if (watchHandle == INVALID_HANDLE_VALUE) 
	{
		DWORD err = GetLastError();
		LOGERROR(err, "FindFirstChangeNotification");
		return false;
	}

	HANDLE poolHandle;
	if(!RegisterWaitForSingleObject(&poolHandle, watchHandle, onEventTriggered, watchHandle, INFINITE, WT_EXECUTEINWAITTHREAD))
	{
		DWORD err = GetLastError();
		LOGERROR(err, "RegisterWaitForSingleObject");
		return false;
	}

	DirWinAPIWait waitStruct = { cb, poolHandle };
	callbacks[watchHandle] = waitStruct;

	return true;
}