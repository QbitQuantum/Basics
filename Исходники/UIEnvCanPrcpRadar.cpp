	ERMsg CUIEnvCanPrcpRadar::Execute(CCallback& callback)
	{
		ERMsg msg;
		string workingDir = GetDir(WORKING_DIR);

		CInternetSessionPtr pSession;
		CHttpConnectionPtr pConnection;

		msg = GetHttpConnection(SERVER_NAME, pConnection, pSession);
		if (!msg)
			return msg;

		callback.AddMessage(GetString(IDS_UPDATE_DIR));
		callback.AddMessage(workingDir, 1);
		callback.AddMessage(GetString(IDS_UPDATE_FROM));
		callback.AddMessage(SERVER_NAME, 1);
		callback.AddMessage("");

		string type = as<size_t>(TYPE) == TYPE_06HOURS ? "06" : "24";
		string path = SERVER_PATH + type + "/*.grib2";


		CFileInfoVector fileList;
		msg = UtilWWW::FindFiles(pConnection, path, fileList);

		callback.AddMessage("Number of images found: " + ToString(fileList.size()));
		//keep only 10km grid
		for (CFileInfoVector::const_iterator it = fileList.begin(); it != fileList.end();)
		{
		//	string fileTitle = GetFileTitle(it->m_filePath);
//			if (Find(fileTitle, "ps10km"))
	//		{
		//		it = fileList.erase(it);
//			}
	//		else
		//	{
			string fileName = GetFileName(it->m_filePath);
			string filePath = GetOutputFilePath(fileName);
			if (!NeedDownload(*it, filePath))
				it = fileList.erase(it);
			else
				it++;
			//}

			msg += callback.StepIt(0);
		}

		//remove up to date file

		//for(int i=fileList.size()-1; i>=0; i--)
		//{
		//	string fileName = GetFileName(fileList[i].m_filePath);
		//	string filePath = GetOutputFilePath(fileName);
		//	if( !NeedDownload(fileList[i], filePath) )
		//		fileList.erase(fileList.begin() + i);

		//	msg += callback.StepIt(0);
		//}



		callback.AddMessage("Number of images to download after clearing: " + ToString(fileList.size()));
		callback.PushTask("Download precipitation images + (" + ToString(fileList.size() )+ ")", fileList.size());
		//callback.SetNbStep(fileList.size());

		int nbDownload = 0;
		for (size_t i = 0; i < fileList.size() && msg; i++)
		{
			string filePath = GetOutputFilePath(GetFileName(fileList[i].m_filePath));
			CreateMultipleDir(GetPath(filePath));
			msg = UtilWWW::CopyFile(pConnection, fileList[i].m_filePath, filePath, INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD | INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_DONT_CACHE);
			if (msg)
				nbDownload++;

			msg += callback.StepIt();
		}

		pConnection->Close();
		pSession->Close();


		callback.AddMessage("Number of images downloaded: " + ToString(nbDownload));
		callback.PopTask();


		return msg;
	}