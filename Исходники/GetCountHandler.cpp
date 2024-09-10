	WebResponse* GetCountHandler::Execute(WebRequest* pWebRequest, WebContext* pWebContext, User* pUser)
	{
		GetCountRequest* pRequest = static_cast<GetCountRequest*>(pWebRequest);

		FeatureClass* pFeatureClass = GetFeatureClass(pWebRequest, pWebContext, pUser);
		if(pFeatureClass==NULL)
		{
			GError* pError = augeGetErrorInstance();
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(pError->GetLastError());
			return pExpResponse;
		}
		
		g_uint fcount = 0;
		GEnvelope& bbox = pRequest->GetBBox(); 
		if(bbox.IsValid()) 
		{
			fcount = pFeatureClass->GetCount(bbox);
		}
		else
		{
			GFilter* pFilter = pRequest->GetFilter(pFeatureClass); 
			fcount = pFeatureClass->GetCount(pFilter);
		}

		WebResponse* pWebResponse = NULL; 
		GetCountResponse *pResponse = new GetCountResponse(pRequest);
		pResponse->SetWebContenxt(pWebContext);
		pResponse->SetCount(fcount);

		pFeatureClass->Release();
		
		return pResponse;
	}