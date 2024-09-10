	void CVLDatabase::Open(const string &provider, const string &dataSource, const string &userId, const string &password,
		IVLDBOpenCallback * callback)
	{
		Close();
		string connectionString = Format(TEXT("Provider=%s;Data Source=%s;"), (LPCTSTR)provider.c_str(), (LPCTSTR)dataSource.c_str());

		try
		{
			HRESULT hr = E_FAIL;
			hr = connection.CreateInstance(__uuidof(Connection));
			if (FAILED(hr)) _com_raise_error(hr);

			hr = recordset.CreateInstance(__uuidof(Recordset));

			if (callback) callback->OnOpenState(string("Opening connection"));

			connection->Open(connectionString.c_str(), userId.c_str(), password.c_str(), adConnectUnspecified);
			connected = true;
			
			if (callback) callback->OnOpenState(string("Retrieving record count"));

			_RecordsetPtr r = connection->Execute((TEXT("SELECT COUNT(ID) AS RC FROM ") + recordsetName).c_str(), NULL, adCmdText);
			int rc = r->Fields->Item["RC"]->Value.lVal;

			if (callback) callback->OnOpenState(string("Allocating memory"));

			allCapacity = VLDBAllCapacity(rc);
			allItems = (VLDBItem**)malloc(sizeof(VLDBItem*) * allCapacity);

			if (callback) callback->OnOpenState(string("Opening recordset in forward only mode"));

			OpenRecordset(adOpenForwardOnly);
			if (callback)
			{
				callback->OnOpenState(string("Loading data"));
				callback->OnOpenProgress(false, rc);
			}
			DWORD dt = GetTickCount();
			while (!recordset->EndOfFile)
			{
				if (callback && GetTickCount() - dt > 300)
				{
					if (!callback->OnOpenProgress(true, allCount)) break;
					dt = GetTickCount();
				}
				if (record.idStatus != adFldOK ||
					record.featuresStatus != adFldOK ||
					record.faceIdStatus != adFldOK)
					throw exception("Can not open database\nError reading data");
				AddItem(record.id, record.features, record.featuresLength,
					record.faceId, record.faceIdLength / sizeof(TCHAR));
				recordset->MoveNext();
			}

			if (callback) callback->OnOpenState(string("Opening recordset"));
			OpenRecordset();
			
			if (callback) callback->OnOpenState(string("Done"));

			this->provider = provider;
			this->dataSource = dataSource;
		}
		catch (_com_error &e)
		{
			if (callback) callback->OnOpenState(string("Error"));
			try
			{
				Close();
			}
			catch (exception &)
			{
				// do nothing
			}
			ComErrorToException(e, string("Can not open database"));
		}
	}