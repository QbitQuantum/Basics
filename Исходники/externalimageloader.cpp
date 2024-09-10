// Load image data
QImage ExternalImageLoader::loadImage()
{
	QImage result;

	// Configuration file loading
	QSettings settings("../res/externalimageloader.ini", QSettings::IniFormat);

	// Get external program, redirection and result file names
	QString program = settings.value("program").toString();
	QString redirection = settings.value("redirection").toString();
	QString filename = settings.value("filename").toString();

	if (program.isEmpty() || filename.isEmpty())
		return result;

	// Ensure program has started
	QProcess process;
	if (!redirection.isEmpty())
		process.setStandardOutputFile(redirection);
	process.start(program);
	if (!process.waitForStarted())
		return result;

	// Get timeout value
	int timeout = settings.value("timeout").toInt();
	QTime timer;
	timer.start();

	// Check for program exit or timeout event
	while (process.state() != QProcess::NotRunning)
	{
		if (timeout > 0 && timer.elapsed() > timeout)
		{
			// Stop process
			process.kill();
			// Try to delete file
			QDir dir;
			dir.remove(filename);
			// Return null image
			return result;
		}

		qApp->processEvents();
	}

	// Ensure program has finished correctly
	if (process.exitStatus() != QProcess::NormalExit)
		return result;

	// Try to read and remove the output file
	result = QImage(filename);
	QDir dir;
	dir.remove(filename);
	return result;
}