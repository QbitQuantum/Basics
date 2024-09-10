void ShareManager::refresh(bool dirs, bool aUpdate, bool block, function<void (float)> progressF) noexcept {
	if(refreshing.test_and_set()) {
		LogManager::getInstance()->message(_("File list refresh in progress, please wait for it to finish before trying to refresh again"));
		return;
	}

	update = aUpdate;
	refreshDirs = dirs;

	join();

	if(block) {
		runRefresh(progressF);
	} else {
		try {
			start();
			setThreadPriority(Thread::LOW);
		} catch(const Exception &e) {
			LogManager::getInstance()->message(_("File list refresh failed: ") + e.getError());
		}
	}
}