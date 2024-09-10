	WebResponse* FeatureProjectHandler::Execute(WebRequest* pWebRequest, WebContext* pWebContext, User* pUser)
	{
		Begin(pUser);

		FeatureProjectRequest* pRequest = static_cast<FeatureProjectRequest*>(pWebRequest);

		const char* input_source_name = pRequest->GetInputSourceName();
		const char* input_type_name	  = pRequest->GetInputTypeName();
		const char* output_source_name= pRequest->GetOutputSourceName();
		const char* output_type_name  = pRequest->GetOutputTypeName();
		g_int output_srid = pRequest->GetOutputSrid();
		
		if(output_srid < 0)
		{
			char msg[AUGE_MSG_MAX] = {0};
			g_sprintf(msg, "Invalie output sird [%d]", output_srid);
			augeGetLoggerInstance()->Error(msg,__FILE__, __LINE__);
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(msg);
			return pExpResponse;
		}

		auge::FeatureProjectProcessor* pProcessor = NULL;
		auge::GProcessorFactory* pFactory = auge::augeGetGeoProcessorFactoryInstance();
		pProcessor = pFactory->CreateFeatureProjectProcessor();

		pProcessor->SetUser(pUser->GetID());
		pProcessor->SetInputDataSource(input_source_name);
		pProcessor->SetInputFeatureClass(input_type_name);

		pProcessor->SetOutputDataSource(output_source_name);
		pProcessor->SetOutputFeatureClass(output_type_name);
		pProcessor->SetOutputSRID(output_srid);

		RESULTCODE rc = pProcessor->Execute();
		pProcessor->Release();

		if(rc != AG_SUCCESS)
		{
			GError* pError = augeGetErrorInstance();
			augeGetLoggerInstance()->Error(pError->GetLastError(),__FILE__, __LINE__);
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(pError->GetLastError());
			return pExpResponse;
		}

		WebSuccessResponse* pSusResponse = augeCreateWebSuccessResponse();
		pSusResponse->SetRequest(pRequest->GetRequest());

		End();

		return pSusResponse;
	}