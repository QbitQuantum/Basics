void TrackingSystemIGSTKService::configure()
{
	if (mConfigurationFilePath.isEmpty() || !QFile::exists(mConfigurationFilePath))
	{
		reportWarning(QString("Configuration file [%1] is not valid, could not configure the toolmanager.").arg(mConfigurationFilePath));
		return;
	}

	//parse
	ConfigurationFileParser configParser(mConfigurationFilePath, mLoggingFolder);

	std::vector<IgstkTracker::InternalStructure> trackers = configParser.getTrackers();

	if (trackers.empty())
	{
		reportWarning("Failed to configure tracking.");
		return;
	}

	IgstkTracker::InternalStructure trackerStructure = trackers[0]; //we only support one tracker atm

	IgstkTool::InternalStructure referenceToolStructure;
	std::vector<IgstkTool::InternalStructure> toolStructures;
	QString referenceToolFile = configParser.getAbsoluteReferenceFilePath();
	std::vector<QString> toolfiles = configParser.getAbsoluteToolFilePaths();
	for (std::vector<QString>::iterator it = toolfiles.begin(); it != toolfiles.end(); ++it)
	{
		ToolFileParser toolParser(*it, mLoggingFolder);
		IgstkTool::InternalStructure internalTool = toolParser.getTool();
		if ((*it) == referenceToolFile)
			referenceToolStructure = internalTool;
		else
			toolStructures.push_back(internalTool);
	}

	//new thread
	mTrackerThread.reset(new IgstkTrackerThread(trackerStructure, toolStructures, referenceToolStructure));

	connect(mTrackerThread.get(), SIGNAL(configured(bool)), this, SLOT(trackerConfiguredSlot(bool)));
	connect(mTrackerThread.get(), SIGNAL(initialized(bool)), this, SLOT(initializedSlot(bool)));
	connect(mTrackerThread.get(), SIGNAL(tracking(bool)), this, SLOT(trackerTrackingSlot(bool)));
	connect(mTrackerThread.get(), SIGNAL(error()), this, SLOT(uninitialize()));

	//start threads
	if (mTrackerThread)
		mTrackerThread->start();
}