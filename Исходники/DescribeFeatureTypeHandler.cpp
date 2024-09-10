	WebResponse* DescribeFeatureTypeHandler::Execute(WebRequest* pWebRequest, WebContext* pWebContext, User* pUser)
	{
		WebResponse* pWebResponse = NULL;
		DescribeFeatureTypeRequest* pRequest = static_cast<DescribeFeatureTypeRequest*>(pWebRequest);
		
		//if(pRequest->IsValidSource())
		//{
		//	pWebResponse = ExecuteBySource(pWebRequest, pWebContext);
		//}
		//else
		//{
		//	pWebResponse = ExecuteByMap(pWebRequest, pWebContext);
		//}

		FeatureClass* pFeatureClass = GetFeatureClass(pWebRequest, pWebContext, pUser);
		if(pFeatureClass==NULL)
		{
			GError* pError = augeGetErrorInstance();
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(pError->GetLastError());
			return pExpResponse;
		}

		char cache_name[AUGE_NAME_MAX];
		char cache_file[AUGE_PATH_MAX];
		const char* typeName = pRequest->GetTypeName();
		const char* cache_path = pWebContext->GetCacheProtocolPath();
		g_snprintf(cache_name, AUGE_NAME_MAX,"%s_wfs_%s_describe_feauretype_1_1_0", pWebContext->GetService(), typeName);
		auge_make_path(cache_file, NULL, cache_path, cache_name,"xml");

		//if(access(capa_path,4))
		{
			WriteDescribeFeatureType(pRequest->GetVersion(), pWebContext, typeName, pFeatureClass);
		}

		pFeatureClass->Release();

		DescribeFeatureTypeResponse* pResponse = new DescribeFeatureTypeResponse(pRequest);		
		pResponse->SetPath(cache_file);

		return pResponse;
	}