Error
ArchiverConnectionTask::contact()
{
#ifdef notdef
	const string hostname(state->getArchiverHost());
	Debug(DEBUG_ARCHIVE, 0, hostname.c_str());
	int32_t port = state->getArchiverPort();
	archiver->setAddress(hostname.c_str(), port);

	Error err;
	while ((err = archiver->establish())) {
		Timer timer;
		timer.sleep(retrySleep);
	}
#else
	Error err = 0;
	do {
		Timer timer;
		timer.sleep(retrySleep);

		const string hostname(state->getArchiverHost());
		Debug(DEBUG_ARCHIVE, 0, hostname.c_str());
		int32_t port = state->getArchiverPort();
		archiver->setAddress(hostname.c_str(), port);
		err = archiver->establish();
	} while (err);
#endif

	Debug(DEBUG_ARCHIVE, 0, "archiver connected");
	return (0);
}