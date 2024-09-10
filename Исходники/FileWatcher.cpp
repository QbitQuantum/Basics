void FileWatcher::Init(const char* path)
{
	strcpy_s(s_fileWatcher.path, path);
	s_fileWatcher.pathLen = (uint)strlen(s_fileWatcher.path);
	s_fileWatcher.nextListenerId = 1;
	s_fileWatcher.hCallbackEvent = CreateEventA(nullptr, false, false, nullptr);
	s_fileWatcher.hChangedTimer = Timer::Create();

	s_fileWatcher.listenerThread = std::thread(fileWatcherListenerThread);
	s_fileWatcher.callbackThread = std::thread(fileWatcherCallbackThread);
}