void QDialogManager::wait(ZLRunnable &runnable, const std::string &message) const {
	QWaitMessage waitMessage(message);
	runnable.run();
}