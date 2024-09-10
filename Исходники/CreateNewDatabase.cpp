void CCreateNewDatabase::RunEx()
{
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);

	// reset values
	m_strQueryCreateItem = "";
	m_iCreateItem = 0;
	
	m_strQueryUpdateItem = "";
	m_iUpdateItem = 0;

	m_strQueryNoUpdateItem = "";
	m_iNoUpdateItem = 0;

	// calculate last run time
	// Scheduler
	SallyAPI::Scheduler::CSchedulerManager* schedulerManager = SallyAPI::Scheduler::CSchedulerManager::GetInstance();
	SYSTEMTIME lastRun = schedulerManager->GetLastSchedulerRun(m_pWindow, "dbcreator");

	//Convert both to FILETIMEs
	m_ftLastRun.dwHighDateTime = 0;
	m_ftLastRun.dwLowDateTime = 0;
	SystemTimeToFileTime(&lastRun, &m_ftLastRun);

	std::string mediaDB = m_strMediaDirectory;
	mediaDB.append("image.db");

	bool bFileExists = SallyAPI::File::FileHelper::FileExistsAndNotEmpty(mediaDB);

	SallyAPI::Database::CDatabaseConnection* dbconn = SallyAPI::Database::CDatabaseConnection::Open(mediaDB);

	dbconn->LockDatabase();
	if (bFileExists == false)
	{
		// Create
		std::string queryCreate;
		queryCreate.append("CREATE TABLE image ( \
						   Filename     TEXT UNIQUE, \
						   DeleteFlag	INTEGER, \
						   Rating		INTEGER, \
						   CreateYear	INTEGER, \
						   CreateMonth	INTEGER \
						   );");
		try
		{
			SallyAPI::Database::CStatement* stmtCreate = dbconn->CreateStatement();
			stmtCreate->Execute(queryCreate.c_str());
		}
		catch (SallyAPI::Database::CSQLException* e)
		{
			SallyAPI::System::CLogger* logger = SallyAPI::Core::CGame::GetLogger();
			logger->Error(e->GetMessage());
		}
	}
	dbconn->ReleaseDatabase();

	// Set Delete Flag
	std::string querySetDelete = "UPDATE image SET DeleteFlag = 1;";

	dbconn->LockDatabase();

	try
	{
		SallyAPI::Database::CStatement* stmtSetDelete = dbconn->CreateStatement();
		stmtSetDelete->Execute(querySetDelete.c_str());
	}
	catch (SallyAPI::Database::CSQLException* e)
	{
		SallyAPI::System::CLogger* logger = SallyAPI::Core::CGame::GetLogger();
		logger->Error(e->GetMessage());
	}

	dbconn->ReleaseDatabase();

	std::vector<std::string>::iterator iter;

	// Collect Information
	for (iter = m_vFolders.begin(); iter != m_vFolders.end(); iter++)
	{
		std::string folder = *iter;
		CollectInformation(folder);

		if (m_bPleaseStop)
		{
			SallyAPI::Database::CDatabaseConnection::Close(mediaDB);
			return;
		}
	}
	m_pProcessbar->SetMaxPosition(m_iFileCount);

	// Create Database
	for (iter = m_vFolders.begin(); iter != m_vFolders.end(); iter++)
	{
		std::string folder = *iter;
		AddFolder(dbconn, folder);

		if (m_bPleaseStop)
		{
			SallyAPI::Database::CDatabaseConnection::Close(mediaDB);
			return;
		}
	}
	// execute rest of the create item statements
	ExecuteCreateItem(dbconn);
	ExecuteUpdateItem(dbconn);
	ExecuteNoUpdateItem(dbconn);

	// Set Delete Flag
	std::string queryDelete;
	queryDelete.append("DELETE FROM image WHERE DeleteFlag = 1;");

	dbconn->LockDatabase();

	try
	{
		SallyAPI::Database::CStatement* stmtDelete = dbconn->CreateStatement();
		stmtDelete->Execute(queryDelete.c_str());
	}
	catch (SallyAPI::Database::CSQLException* e)
	{
		SallyAPI::System::CLogger* logger = SallyAPI::Core::CGame::GetLogger();
		logger->Error(e->GetMessage());
	}

	dbconn->ReleaseDatabase();

	SallyAPI::Database::CDatabaseConnection::Close(mediaDB);

	m_pWindow->SendMessageToParent(0, 0, m_iMessageId);
}