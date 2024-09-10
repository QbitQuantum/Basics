	WebResponse* CreateMapHandler::Execute(WebRequest* pWebRequest, User* pUser)
	{	
		CreateMapRequest* pRequest = static_cast<CreateMapRequest*>(pWebRequest);

		const char* name = pRequest->GetName();
		if(name==NULL)
		{
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage("Parameter [name] is NULL");
			return pExpResponse;
		}

		Map* pMap = NULL;
		CartoManager* pCartoManager = NULL;
		pCartoManager = augeGetCartoManagerInstance();
		pMap = pCartoManager->LoadMap(pUser->GetID(), name);
		if(pMap)
		{
			char msg[AUGE_MSG_MAX];
			g_sprintf(msg, "Map %s already exists.", name);
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(msg);
			return pExpResponse;
		}

		const char* extent = pRequest->GetExtent(); 
		if(extent==NULL)
		{
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage("Parameter extent is null.");
			return pExpResponse;
		}

		double xmin=0.0f, ymin=0.0f, xmax=0.0f, ymax=0.0f;
		sscanf(extent,"%lf,%lf,%lf,%lf",&xmin, &ymin, &xmax, &ymax);
		int srid = atoi(pRequest->GetSRID());
		pMap = pCartoManager->CreateMap(pUser->GetID(), name, srid, xmin, ymin, xmax, ymax);
		if(!pMap)
		{
			GError* pError = augeGetErrorInstance();
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(pError->GetLastError());
			return pExpResponse;
		}				
		WebSuccessResponse* pSusResponse = augeCreateWebSuccessResponse();
		pSusResponse->SetRequest("CreateMap");
		return pSusResponse;
	}