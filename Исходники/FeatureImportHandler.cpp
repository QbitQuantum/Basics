	/// <summary>
	/// Imports the shape file.
	/// </summary>
	/// <param name="shp_path">The shp_path.</param>
	/// <param name="shp_name">The shp_name.</param>
	/// <param name="source_name">The source_name.</param>
	/// <param name="type_name">The type_name.</param>
	/// <returns></returns>
	WebResponse* FeatureImportHandler::ImportShapeFile(const char* shp_path, const char* shp_name, const char* source_name, const char* type_name, User* pUser)
	{
		WebResponse* pWebResponse = NULL;

		GError* pError = augeGetErrorInstance();
		GLogger* pLogger = augeGetLoggerInstance();

		GProcessorFactory* factory = augeGetGeoProcessorFactoryInstance();
		FeatureImportProcessor* processor = factory->CreateFeatureImportProcessor();

		processor->SetUser(pUser->GetID());
		processor->SetShapePath(shp_path);
		processor->SetShapeName(shp_name);
		processor->SetDataSourceName(source_name);
		processor->SetFeatureClassName(type_name);

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
			pSusResponse->SetRequest("FeatureImport");
			pWebResponse = pSusResponse;
		}

		processor->Release();

		return pWebResponse;
	}