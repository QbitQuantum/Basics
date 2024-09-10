bool hasAntiword()
{
	static bool searched = false, found = false;
	if (searched) // searched already in this run
		return found;

	QProcess *test = new QProcess();
	QString exename("antiword");
#if defined(_WIN32)
	exename = ScPaths::instance().libDir() + "tools/antiword/antiword.exe";
#endif
	test->start(exename, QStringList());
	if (test->waitForStarted())
	{
		found = true;
		test->terminate();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		test->kill();	
	}
	delete test;
	searched = true;
	return found;
}