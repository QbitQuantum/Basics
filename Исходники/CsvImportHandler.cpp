	/// <summary>
	/// Imports the shape file.
	/// </summary>
	/// <param name="csv_path">The csv_path.</param>
	/// <param name="csv_name">The csv_name.</param>
	/// <param name="source_name">The source_name.</param>
	/// <param name="type_name">The type_name.</param>
	/// <returns></returns>
	WebResponse* CsvImportHandler::ImportCsvFile(const char* csv_path, const char* csv_name, const char* source_name, const char* type_name, g_int user_id)
	{
		WebResponse* pWebResponse = NULL;

		GError* pError = augeGetErrorInstance();
		GLogger* pLogger = augeGetLoggerInstance();

		GProcessorFactory* factory = augeGetGeoProcessorFactoryInstance();
		CsvImportProcessor* processor = factory->CreateCsvImportProcessor();

		char local_csv_path[AUGE_PATH_MAX];
		memset(local_csv_path, 0, AUGE_PATH_MAX);
		auge_make_path(local_csv_path, NULL, csv_path, csv_name, NULL);

		processor->SetUser(user_id);
		processor->SetCsvPath(local_csv_path);
		processor->SetDataSource(source_name);
		processor->SetDatasetName(type_name);

		RESULTCODE rc = processor->Execute();
		if(rc!=AG_SUCCESS)
		{
			GError* pError = augeGetErrorInstance();
			pLogger->Error(pError->GetLastError());
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(pError->GetLastError());
			pWebResponse =  pExpResponse;
		}
		else
		{
			WebSuccessResponse* pSusResponse = augeCreateWebSuccessResponse();
			pSusResponse->SetRequest("CsvImport");
			pWebResponse = pSusResponse;
		}

		processor->Release();

		return pWebResponse;
	}