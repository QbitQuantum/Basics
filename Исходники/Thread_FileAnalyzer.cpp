void FileAnalyzer::run()
{
	m_bSuccess.fetchAndStoreOrdered(0);

	m_tasksCounterNext = 0;
	m_tasksCounterDone = 0;
	m_completedCounter = 0;

	m_completedFiles.clear();
	m_completedTaskIds.clear();
	m_runningTaskIds.clear();

	m_filesAccepted = 0;
	m_filesRejected = 0;
	m_filesDenied = 0;
	m_filesDummyCDDA = 0;
	m_filesCueSheet = 0;

	m_timer->invalidate();

	//Sort files
	MUtils::natural_string_sort(m_inputFiles, true);

	//Handle playlist files first!
	handlePlaylistFiles();

	const unsigned int nFiles = m_inputFiles.count();
	if(nFiles < 1)
	{
		qWarning("File list is empty, nothing to do!");
		return;
	}

	//Update progress
	emit progressMaxChanged(nFiles);
	emit progressValChanged(0);

	//Create the thread pool
	if (m_pool.isNull())
	{
		m_pool.reset(new QThreadPool());
	}

	//Update thread count
	const int idealThreadCount = QThread::idealThreadCount();
	if(idealThreadCount > 0)
	{
		m_pool->setMaxThreadCount(qBound(2, ((idealThreadCount * 3) / 2), 12));
	}

	//Start first N threads
	QTimer::singleShot(0, this, SLOT(initializeTasks()));

	//Start event processing
	this->exec();

	//Wait for pending tasks to complete
	m_pool->waitForDone();

	//Was opertaion aborted?
	if(MUTILS_BOOLIFY(m_bAborted))
	{
		qWarning("Operation cancelled by user!");
		return;
	}
	
	//Update progress
	emit progressValChanged(nFiles);

	//Emit pending files (this should not be required though!)
	if(!m_completedFiles.isEmpty())
	{
		qWarning("FileAnalyzer: Pending file information found after last thread terminated!");
		QList<unsigned int> keys = m_completedFiles.keys(); qSort(keys);
		while(!keys.isEmpty())
		{
			emit fileAnalyzed(m_completedFiles.take(keys.takeFirst()));
		}
	}

	qDebug("All files added.\n");
	m_bSuccess.fetchAndStoreOrdered(1);
	QThread::msleep(333);
}