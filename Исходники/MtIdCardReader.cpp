std::string CMtIdCardReader::ReadIdCardInfo()
{
	Json::Value root; 
	Json::Value JsonReadInfo;
	Json::Value JsonUserInfo;
	string json_content = "";
	int nRes = 0;
	int rlen = 0;
	char msg[MAX_PATH] = {0};
	unsigned char pData[MAX_PATH*10] = {0};
	char szfilename[MAX_PATH] = {0};
	char sztmpfolder[MAX_PATH]  = {0};
	std::string szoldimgpath;
	//GetTempPathA(MAX_PATH,sztmpfolder);
	GetSystemDirectoryA(sztmpfolder,MAX_PATH);
	sztmpfolder[3] = '\0';
	szoldimgpath = szoldimgpath + sztmpfolder+ "zp.bmp";

	HANDLE icdev = m_IdCardReaderMgr.pFun_device_open(0,9600);
	nRes = m_IdCardReaderMgr.pFun_IDCard_ReadCard(icdev,msg);
	JsonReadInfo["message"] = msg;
	JsonReadInfo["code"] = nRes;
	if(!nRes)
	{
		m_IdCardReaderMgr.pFun_IDCard_SetPhotoPath(sztmpfolder);
		nRes = m_IdCardReaderMgr.pFun_IDCard_Read(icdev,&rlen,pData);
		if(!nRes)
		{
			for (int i=0;i<=10;i++)
			{
				char sztmp[MAX_PATH] = {0};
				m_IdCardReaderMgr.pFun_IDCard_GetCardInfo(icdev,i,sztmp);
				JsonUserInfo[m_mapfield[i]]=sztmp;
			}
			JsonReadInfo["userInfo"] = JsonUserInfo;
			//铭泰的保存图片接口有问题不能设置保存名字。删除先前旧的照片.
			if(_access((char*)szoldimgpath.c_str(), 0) == 0)
			{
				CopyFileA(szoldimgpath.c_str(),m_strimgPath.c_str(),FALSE);
				DeleteFileA(szoldimgpath.c_str());
				JsonReadInfo["userInfo"]["img"] = m_strimgPath;
			}
		}
	}

	


	Json::StyledWriter writer;  
	json_content = writer.write(JsonReadInfo); 
	m_IdCardReaderMgr.pFun_device_close(icdev);
	return json_content;
}