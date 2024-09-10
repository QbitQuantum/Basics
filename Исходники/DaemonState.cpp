void DaemonState::start(bool forceFullScan)
{
	// Disable implicit flushing after a change
	WorkerThread::immediateFlush(false);

	// Do full scans ?
	if (forceFullScan == true)
	{
		m_fullScan = true;
	}
	else
	{
		Rand randomStuff;
		guint32 randomArray[5];

		randomStuff.set_seed(randomArray[2]);
		int randomNum = randomStuff.get_int_range(0, 10);
		if (randomNum >= 7)
		{
			m_fullScan = true;
		}
#ifdef DEBUG
		cout << "DaemonState::start: picked " << randomNum << endl;
#endif
	}

	// Fire up the mail monitor thread now
	m_pMailHandler = new MboxHandler();
	MonitorThread *pMailMonitorThread = new MonitorThread(m_pMailMonitor, m_pMailHandler);
	pMailMonitorThread->getDirectoryFoundSignal().connect(SigC::slot(*this, &DaemonState::on_message_filefound));
	start_thread(pMailMonitorThread, true);

	// Same for the disk monitor thread
	m_pDiskHandler = new OnDiskHandler();
	MonitorThread *pDiskMonitorThread = new MonitorThread(m_pDiskMonitor, m_pDiskHandler);
	pDiskMonitorThread->getDirectoryFoundSignal().connect(SigC::slot(*this, &DaemonState::on_message_filefound));
	start_thread(pDiskMonitorThread, true);

	set<PinotSettings::IndexableLocation>::const_iterator locationIter = PinotSettings::getInstance().m_indexableLocations.begin();
	if (locationIter != PinotSettings::getInstance().m_indexableLocations.end())
	{
		// Crawl this now
		crawlLocation(locationIter->m_name, true, locationIter->m_monitor);
	}
}