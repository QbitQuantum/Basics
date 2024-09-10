	WebResponse* AddRasterHandler::Execute(WebRequest* pWebRequest, WebContext* pWebContext, User* pUser)
	{
		GLogger* pLogger = augeGetLoggerInstance();
		AddRasterRequest* pRequest = static_cast<AddRasterRequest*>(pWebRequest);

		const char* raster_name = pRequest->GetRasterName();
		const char* folder_path = pRequest->GetRasterPath();
		const char* file_path   = pRequest->GetFilePath();

		if(raster_name==NULL)
		{
			const char* msg = "Parameter [Name] is NULL";
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(msg);
			pLogger->Error(msg,__FILE__,__LINE__);

			return pExpResponse;
		}
		const char* sourceName = pRequest->GetSourceName();
		if(sourceName==NULL)
		{
			const char* msg = "Parameter [SourceName] is NULL";
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(msg);
			pLogger->Error(msg,__FILE__,__LINE__);

			return pExpResponse;
		}
		if(file_path==NULL)
		{
			const char* msg = "Parameter [filePath] is NULL";
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(msg);
			pLogger->Error(msg,__FILE__,__LINE__);

			return pExpResponse;
		}

		Workspace* pWorkspace = NULL;
		RasterWorkspace* pRasterWorkspace = NULL;
		ConnectionManager* pConnectionManager = NULL;
		pConnectionManager = augeGetConnectionManagerInstance();
		pWorkspace = pConnectionManager->GetWorkspace(pUser->GetID(), sourceName);
		if(pWorkspace==NULL)
		{
			char msg[AUGE_MSG_MAX];
			memset(msg,0,AUGE_MSG_MAX);
			g_sprintf(msg,"Cannot Get DataSource [%s]", sourceName);
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(msg);
			pLogger->Error(msg,__FILE__,__LINE__);

			return pExpResponse;
		}

		pRasterWorkspace = dynamic_cast<RasterWorkspace*>(pWorkspace);
		//if(pRasterWorkspace==NULL)
		//{
		//	char msg[AUGE_MSG_MAX];
		//	memset(msg,0,AUGE_MSG_MAX);
		//	g_sprintf(msg,"Cannot Get DataSource [%s]", sourceName);
		//	WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
		//	pExpResponse->SetMessage(msg);
		//	pLogger->Error(msg,__FILE__,__LINE__);

		//	return pExpResponse;
		//}

		RasterFolder* pFolder = pRasterWorkspace->GetFolder(folder_path);
		if(pFolder==NULL)
		{
			char msg[AUGE_MSG_MAX];
			g_sprintf(msg, "Path [%s] does not exist.", folder_path);
			GLogger* pLogger = augeGetLoggerInstance();
			pLogger->Error(msg, __FILE__, __LINE__);
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(msg);
			return pExpResponse;
		}

		char user_file_root[AUGE_PATH_MAX];
		auge_make_user_file_root(user_file_root, AUGE_PATH_MAX, pWebContext->GetUserRoot(), pUser->GetName());

		char file_local_path[AUGE_PATH_MAX];
		memset(file_local_path, 0, AUGE_PATH_MAX);
		auge_make_path(file_local_path,  NULL, user_file_root, file_path+1, NULL);
		if(g_access(file_local_path,4))
		{
			char msg[AUGE_MSG_MAX];
			g_snprintf(msg, AUGE_MSG_MAX, "File [%s] does not exist", file_path);
			GLogger* pLogger = augeGetLoggerInstance();
			pLogger->Error(msg, __FILE__, __LINE__);
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(msg);
			return pExpResponse;
		}

		char uuid[AUGE_PATH_MAX] = {0};
		auge_generate_uuid(uuid, AUGE_PATH_MAX);

		RESULTCODE rc = AG_FAILURE;
		RasterDataset* pRasterDataset = pFolder->GetRasterDataset();
		rc = pRasterDataset->AddRaster(raster_name, file_local_path, uuid);
		if(rc != AG_SUCCESS )
		{
			pFolder->Release();

			GError* pError = augeGetErrorInstance();			
			GLogger* pLogger = augeGetLoggerInstance();
			pLogger->Error(pError->GetLastError(), __FILE__, __LINE__);
			WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
			pExpResponse->SetMessage(pError->GetLastError());
			return pExpResponse;
		}

		pFolder->Release();

		//生成thumbnail
		//char thumbnail_path[AUGE_PATH_MAX];
		//memset(thumbnail_path, 0, AUGE_PATH_MAX);
		//auge_make_path(thumbnail_path, NULL, pWebContext->GetThumbnailPath(), uuid, AUGE_THUMBNAIL_SUFFIX);

		//RasterThumbnailProcessor* pProcessor = NULL;
		//GProcessorFactory* pFactory = augeGetGeoProcessorFactoryInstance();
		//pProcessor = pFactory->CreateRasterThumbnailProcessor();
		//pProcessor->SetInputRaster(file_local_path);
		//pProcessor->SetOutputRaster(thumbnail_path);
		//pProcessor->SetThumbSize(512);
		//pProcessor->Execute();
		//pProcessor->Release();

		////计算raster的根目录
		//char raster_repository[AUGE_PATH_MAX];
		//memset(raster_repository, 0, AUGE_PATH_MAX);
		//rds_get_raster_repository(raster_repository, AUGE_PATH_MAX, pUser->GetName(), pWebContext);
		////计算导入后的raster的路径
		//char raster_local_folder[AUGE_PATH_MAX];
		//auge_make_path(raster_local_folder, NULL, raster_repository, raster_path+1, NULL);
		//char raster_local_path[AUGE_PATH_MAX];
		//auge_make_path(raster_local_path, NULL, raster_local_folder, raster_name, NULL);

		//if(g_access(raster_local_folder,4))
		//{
		//	char msg[AUGE_MSG_MAX];
		//	memset(msg,0,AUGE_MSG_MAX);
		//	g_sprintf(msg,"raster path [%s] does not exist.", raster_path);
		//	WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
		//	pExpResponse->SetMessage(msg);
		//	pLogger->Error(msg,__FILE__,__LINE__);

		//	return pExpResponse;
		//}

		////计算待导入的raster文件的本地路径
		//char file_local_path[AUGE_PATH_MAX];
		//memset(file_local_path,0,AUGE_PATH_MAX);
		//auge_make_path(file_local_path,NULL,pWebContext->GetUploadPath(), file_path+1,NULL);

		//// whether file exists.
		//if(g_access(file_local_path,4))
		//{
		//	char msg[AUGE_MSG_MAX];
		//	memset(msg,0,AUGE_MSG_MAX);
		//	g_sprintf(msg,"raster [%s] does not exist.", file_path);
		//	WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
		//	pExpResponse->SetMessage(msg);
		//	pLogger->Error(msg,__FILE__,__LINE__);

		//	return pExpResponse;
		//}

		//RESULTCODE rc = AG_FAILURE;
		//Raster* pRaster = NULL;
		//RasterIO* rio = augeGetRasterIOInstance();
		//pRaster = rio->Read(file_local_path);
		//if(pRaster==NULL)
		//{
		//	char msg[AUGE_MSG_MAX];
		//	memset(msg,0,AUGE_MSG_MAX);
		//	g_sprintf(msg,"Fail to read raster [%s]", file_path);
		//	WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
		//	pExpResponse->SetMessage(msg);
		//	pLogger->Error(msg,__FILE__,__LINE__);

		//	return pExpResponse;
		//}
		//pRaster->SetName(raster_name);
		//pRaster->SetAlias(raster_name);
		//pRaster->SetPath(raster_path);
		////rc = pRasterWorkspace->AddRaster(pRaster);
		//pRaster->Release();

		//if(rc!=AG_SUCCESS)
		//{
		//	GError* pError = augeGetErrorInstance();
		//	WebExceptionResponse* pExpResponse = augeCreateWebExceptionResponse();
		//	pExpResponse->SetMessage(pError->GetLastError());
		//	pLogger->Error(pError->GetLastError(),__FILE__,__LINE__);

		//	return pExpResponse;
		//}

		//auge_move(file_local_path, raster_local_path);

		WebSuccessResponse* pSusResponse = augeCreateWebSuccessResponse();
		pSusResponse->SetRequest(pRequest->GetRequest());
		return pSusResponse;
	}