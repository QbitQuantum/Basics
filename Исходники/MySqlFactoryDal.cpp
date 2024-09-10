/// delete firmware transfers when older than 7 days, regardless of the download status
/// TODO: keep application alerts longer
void MySqlFactoryDal::CleanupOldAlarmsAndFW(nlib::DateTime olderThanDate)
{
	nlib::DateTime currTime = nlib::CurrentUniversalTime();

	const char *pszQry[] ={
		"DELETE FROM FirmwareDownloads WHERE StartedOn < \"%s\";",	// +24*7
		"DELETE FROM AlertNotifications WHERE AlertTime < \"%s\";" };

		LOG("DEBUG CleanupOldRecords for Alarms and FW START [%s] [%s]", nlib::ToString(olderThanDate).c_str(), nlib::ToString(currTime - nlib::util::hours(24*1)).c_str());
		for( int i = 0; i< sizeof(pszQry) / sizeof(pszQry[0]); ++i)
		{	char szQry[ 1024 ];
		snprintf( szQry, sizeof(szQry), pszQry[i], (i>=1)
			? nlib::ToString(olderThanDate).c_str() 
			: (nlib::ToString(currTime - nlib::util::hours(24*7)).c_str()) );
		szQry[ sizeof(szQry)-1 ] = 0;
		std::string obQry( szQry );
		MySQLCommand command(connection, obQry);
		try
		{
			BeginTransaction();
			command.ExecuteNonQuery();
			CommitTransaction();
		}
		catch(std::exception& ex)
		{
			LOG_ERROR("CATCH(exception): CleanupOldRecords failed at step=" << i << " error=" << ex.what());
			RollbackTransaction();
		}
		catch(...)
		{
			LOG_ERROR("CATCH(...): CleanupOldRecords failed at step=" << i );
			RollbackTransaction();
		}
		}
		LOG_STR("DEBUG CleanupOldRecords for Alarms and FW END");
}