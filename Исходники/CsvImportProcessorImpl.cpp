	RESULTCODE CsvImportProcessorImpl::Execute()
	{
		GError	*pError  = augeGetErrorInstance();
		GLogger	*pLogger = augeGetLoggerInstance();

		char csvDrv[AUGE_DRV_MAX];
		char csvDir[AUGE_PATH_MAX];
		char csvName[AUGE_NAME_MAX];
		char csvPath[AUGE_PATH_MAX];
		char constr[AUGE_PATH_MAX];
		memset(csvDrv, 0, AUGE_DRV_MAX);
		memset(csvDir, 0, AUGE_PATH_MAX);
		memset(csvName, 0, AUGE_NAME_MAX);
		memset(csvPath, 0, AUGE_PATH_MAX);
		memset(constr,0,AUGE_PATH_MAX);

		auge_split_path(m_csv_path.c_str(), csvDrv, csvDir,csvName,NULL);
		auge_make_path(csvPath, csvDrv,csvDir,NULL,NULL);
		g_sprintf(constr,"DATABASE=%s",csvPath);

		DataEngine* pDataEngine = NULL;
		DataEngineManager* pDataEngineManager = augeGetDataEngineManagerInstance();
		pDataEngine = pDataEngineManager->GetEngine("CsvFile");
		if(pDataEngine==NULL)
		{
			pLogger->Error(pError->GetLastError(),__FILE__,__LINE__);
			return AG_FAILURE;
		}
		
		RESULTCODE rc = AG_FAILURE;
		Workspace* pcsvWorkspace = pDataEngine->CreateWorkspace();
		pcsvWorkspace->SetConnectionString(constr);
		rc = pcsvWorkspace->Open();
		if(rc!=AG_SUCCESS)
		{
			pLogger->Error(pError->GetLastError(),__FILE__,__LINE__);

			pcsvWorkspace->Release();
			return AG_FAILURE;
		}

		FeatureWorkspace* pobjWorkspace = NULL;
		ConnectionManager* pConnectionManager = augeGetConnectionManagerInstance();
		pobjWorkspace = dynamic_cast<FeatureWorkspace*>(pConnectionManager->GetWorkspace(m_user, m_source_name.c_str()));
		if(pobjWorkspace==NULL)
		{
			pLogger->Error(pError->GetLastError(),__FILE__,__LINE__);

			pcsvWorkspace->Release();
			return AG_FAILURE;
		}

		FeatureClass* pFeatureClass = NULL;
		pFeatureClass = pobjWorkspace->OpenFeatureClass(m_dataset_name.c_str());
		if(pFeatureClass==NULL)
		{
			pLogger->Error(pError->GetLastError(),__FILE__,__LINE__);
			pcsvWorkspace->Release();
			return AG_FAILURE;
		}

		AttributeDataSet* pcsvDataset = static_cast<AttributeDataSet*>(pcsvWorkspace->OpenDataSet(csvName));
		GFields* pcsvFields = pcsvDataset->GetFields();
		GFields* pobjFields = pFeatureClass->GetFields();
		if(!IsMatch(pcsvFields,pobjFields))
		{
			const char* msg = "Field is not matched";
			pError->SetError(msg);
			pLogger->Error(msg, __FILE__, __LINE__);

			pFeatureClass->Release();
			pcsvDataset->Release();
			pcsvWorkspace->Release();
			return AG_FAILURE;
		}

		FeatureInsertCommand* cmd = pFeatureClass->CreateInsertCommand();

		Row* pRow = NULL;
		Cursor* pCursor = pcsvDataset->GetRows();
		while((pRow=pCursor->NextRow())!=NULL)
		{
			AddFeature(pRow, pFeatureClass,cmd);

			pRow->Release();
		}
		cmd->Commit();
		cmd->Release();
		pCursor->Release();		

		pFeatureClass->Refresh();
		pFeatureClass->Release();
		pcsvDataset->Release();
		pcsvWorkspace->Release();

		return AG_SUCCESS;
	}