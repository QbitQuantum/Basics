void GtkDialogManager::wait(ZLRunnable &runnable, const std::string &message) const {
	GtkWaitMessage waitMessage(myWindow, message);
	runnable.run();
}