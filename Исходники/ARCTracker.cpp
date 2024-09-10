bool ARCStringTracker::DumpTracker(std::ostream& os)
{
	bool bNoError = true;

	os.setf(std::ios::hex);

	os << "Dumping ARCStringTracker tracker..." << std::endl;

	//------------------------------------------------------------
	// 
	try
	{
		os << "\t" << "The tracker is (" << convHex((unsigned long)&m_whoami) << " -> " << convHex((unsigned long)m_whoami) << ")\"" << readStringCarefully(m_whoami) << "\"." << std::endl;
	}
	catch (std::string& e)
	{
		os << std::endl << "Dumping failed(" << e << ")." << std::endl;
		bNoError = false;
	}
	//------------------------------------------------------------


	//------------------------------------------------------------
	// 
	try
	{
		os << "\t" << "The last track string is (" << convHex((unsigned long)m_lastStringTrackerName) << ")\"" << readStringCarefully(m_lastStringTrackerName) << "\"." << std::endl;
	}
	catch (std::string& e)
	{
		os << std::endl << "Dumping failed(" << e << ")." << std::endl;
		bNoError = false;
	}
	//------------------------------------------------------------


	//------------------------------------------------------------
	// 
#	ifdef _USE_CLASS_METHOD_TRACK_INCLUDE_STACK_
	os << "Dumping stack tracker..." << std::endl;
	try
	{
		ARCStringTracker* pTracker = m_lastStringTracker;
		while (pTracker)
		{
			if (checkReadable(pTracker, sizeof(ARCStringTracker)))
				throw std::string("ARCStringTracker corrupted");

			os << "\t(" << convHex((unsigned long)pTracker) << " -> " << convHex((unsigned long)pTracker->m_pTrackString) << ")" << readStringCarefully(pTracker->m_pTrackString) << std::endl;
			pTracker = pTracker->m_preStringTracker;
		}
	}
	catch (std::string& e)
	{
		os << std::endl << "Dumping failed(" << e << ")." << std::endl;
		bNoError = false;
	}
	os << "Dumping stack tracker finished." << std::endl;

	os << "Dumping stack tracker stored image..." << std::endl;
	std::vector<TrackRecord>::iterator ite = m_recs.begin();
	std::vector<TrackRecord>::iterator iteEn = m_recs.end();
	for (;ite!=iteEn;ite++)
	{
		const TrackRecord& rec = *ite;
		os << "\t(" << convHex((unsigned long)rec.pTracker) << " -> " << convHex((unsigned long)rec.pString) << ")" << readStringCarefully(rec.pString) << std::endl;
	}
	os << "Dumping stack tracker stored image finished." << std::endl;

#	endif // _USE_CLASS_METHOD_TRACK_INCLUDE_STACK_
	//------------------------------------------------------------

	os << std::endl << "All dumps finished." << std::endl << std::endl;

	__time64_t now;
	_time64( &now );
	os << "UTC time:   " << asctime( _gmtime64( &now ) )    << std::endl;
	os << "Local time: " << asctime( _localtime64( &now ) ) << std::endl;
	return bNoError;
}