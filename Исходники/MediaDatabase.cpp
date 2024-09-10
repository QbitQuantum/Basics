void CMediaDatabase::GetStatisticFromDatabase(SallyAPI::GUI::CAppBase* appBase, SallyAPI::GUI::CListViewExt* listView, int type, int advancedType)
{
	listView->Clear();

	std::string mediaDirectory = SallyAPI::System::SallyHelper::GetMediaDirectory(appBase);
	mediaDirectory.append("media.db");

	bool bFileExists = SallyAPI::File::FileHelper::FileExistsAndNotEmpty(mediaDirectory);
	if (!bFileExists)
		return;

	SallyAPI::Database::CDatabaseConnection* dbconn = SallyAPI::Database::CDatabaseConnection::Open(mediaDirectory);

	std::string query;
	switch (type)
	{
	case 0:
		query.append("SELECT Filename, Type, Artist, Title, Album FROM media WHERE PlayTime != 0 ORDER BY PlayTime DESC LIMIT 200;");
		break;
	case 1:
		query.append("SELECT Filename, Type, Artist, Title, Album FROM media WHERE PlayTime = 0 ORDER BY Title ASC LIMIT 200;");
		break;
	case 2:
		query.append("SELECT Filename, Type, Artist, Title, Album FROM media WHERE Rating = 5 ORDER BY Title ASC LIMIT 200;");
		break;
	case 3:
		query.append("SELECT Filename, Type, Artist, Title, Album FROM media WHERE Rating = 4 ORDER BY Title ASC LIMIT 200;");
		break;
	case 4:
		query.append("SELECT Filename, Type, Artist, Title, Album FROM media WHERE Rating = 3 ORDER BY Title ASC LIMIT 200;");
		break;
	case 5:
		query.append("SELECT Filename, Type, Artist, Title, Album FROM media WHERE Rating = 2 ORDER BY Title ASC LIMIT 200;");
		break;
	case 6:
		query.append("SELECT Filename, Type, Artist, Title, Album FROM media WHERE Rating = 1 ORDER BY Title ASC LIMIT 200;");
		break;
	case 7:
		query.append("SELECT Filename, Type, Artist, Title, Album FROM media WHERE Rating = 0 ORDER BY Title ASC LIMIT 200;");
		break;
	case 8:
		query.append("SELECT Filename, Type, Artist, Title, Album FROM media ORDER BY DBAddDate DESC, Title ASC LIMIT 200;");
		break;
	case 9:
		query.append("SELECT Filename, Type, Artist, Title, Album FROM media WHERE PlayTime > 10 AND ");
		
		SYSTEMTIME dateToConvert;
		SYSTEMTIME currentDate;

		GetSystemTime(&currentDate);

		dateToConvert.wDay = currentDate.wDay;

		dateToConvert.wHour = 0;
		dateToConvert.wMinute = 0;
		dateToConvert.wSecond = 0;

		switch (advancedType)
		{
		case 0:
			if (currentDate.wMonth == 1)
			{
				currentDate.wMonth = 12;
				dateToConvert.wYear = currentDate.wYear - 1;
			}
			else
			{
				dateToConvert.wMonth = currentDate.wMonth - 1;
				dateToConvert.wYear = currentDate.wYear;
			}
			break;
		case 1:
			if (currentDate.wMonth <= 6)
			{
				currentDate.wMonth = 12 - ((currentDate.wMonth - 6) * -1);
				dateToConvert.wYear = currentDate.wYear - 1;
			}
			else
			{
				dateToConvert.wMonth = currentDate.wMonth - 6;
				dateToConvert.wYear = currentDate.wYear;
			}
			break;
		case 2:
			dateToConvert.wMonth = currentDate.wMonth;
			dateToConvert.wYear = currentDate.wYear - 1;
			break;
		case 3:
			dateToConvert.wMonth = currentDate.wMonth;
			dateToConvert.wYear = currentDate.wYear - 2;
			break;
		case 4:
			dateToConvert.wMonth = currentDate.wMonth;
			dateToConvert.wYear = currentDate.wYear - 3;
			break;
		case 5:
			dateToConvert.wMonth = currentDate.wMonth;
			dateToConvert.wYear = currentDate.wYear - 4;
			break;
		case 6:
			dateToConvert.wMonth = currentDate.wMonth;
			dateToConvert.wYear = currentDate.wYear - 5;
			break;
		}
		std::string oderThan = SallyAPI::Date::DateHelper::GetDateString(dateToConvert, false);

		query.append("LastPlayDate < '");
		query.append(oderThan);
		query.append("'");
		query.append(" ORDER BY LastPlayDate ASC LIMIT 200;");
		break;
	}


	dbconn->LockDatabase();
	SallyAPI::Database::CStatement* stmt = dbconn->CreateStatement();

	try
	{
		SallyAPI::Database::CResultSet* rslt = stmt->ExecuteQuery(query.c_str());

		while (rslt->Next())
		{
			std::string sDBFilename = rslt->GetString(1);
			std::string sDBArtist = rslt->GetString(3);
			std::string sDBTitle = rslt->GetString(4);
			std::string sDBAlbum = rslt->GetString(5);

			sDBArtist = SallyAPI::String::StringHelper::ReplaceString(sDBArtist, "#", "'");
			sDBTitle = SallyAPI::String::StringHelper::ReplaceString(sDBTitle, "#", "'");
			sDBFilename = SallyAPI::String::StringHelper::ReplaceString(sDBFilename, "#", "'");
			sDBAlbum = SallyAPI::String::StringHelper::ReplaceString(sDBAlbum, "#", "'");

			std::string firstLine = "";

			if ((sDBTitle.length() != 0) && (sDBArtist.length() != 0))
			{
				firstLine.append(sDBArtist);
				firstLine.append(" - ");
				firstLine.append(sDBTitle);
			}
			else
			{
				firstLine.append(SallyAPI::String::PathHelper::GetFileFromPath(sDBFilename));
			}

			SallyAPI::GUI::CListViewItem listItem(sDBFilename);

			listItem.SetImageId(GUI_THEME_SALLY_ICON_ADD, 0);

			if (rslt->GetInt(2))
				listItem.SetImageId(GUI_THEME_SALLY_ICON_MIMETYPE_VIDEO, 1);
			else
				listItem.SetImageId(GUI_THEME_SALLY_ICON_MIMETYPE_MP3, 1);
			listItem.SetText(firstLine, 1);
			listItem.SetText(sDBAlbum, 2);

			listItem.SetSmallFont(true, 0);
			listItem.SetSmallFont(false, 1);
			listItem.SetSmallFont(true, 2);

			listItem.SetLocalised(SallyAPI::GUI::LISTVIEW_LOCALISATION_FALSE, 1);
			listItem.SetLocalised(SallyAPI::GUI::LISTVIEW_LOCALISATION_FALSE, 2);

			listView->AddItem(listItem);
		}
	}
	catch (SallyAPI::Database::CSQLException* e)
	{
		SallyAPI::System::CLogger* logger = SallyAPI::Core::CGame::GetLogger();
		logger->Error(e->GetMessage());
	}
	dbconn->ReleaseDatabase();

	SallyAPI::Database::CDatabaseConnection::Close(mediaDirectory);
}