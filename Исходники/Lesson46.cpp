void loadmodels()
{
	WIN32_FIND_DATA FindFileData = {0};
    char sTmp[256] = {0};

	ModelNumWater=GetPrivateProfileInt("Set","ModelNumWater",10,".\\Model.ini");
	pModelIDWater=new int[ModelNumWater];
	sprintf(sTmp,"Data/Model/Waters/*.dds");
	HANDLE hFind = ::FindFirstFile(sTmp, &FindFileData);
	if(INVALID_HANDLE_VALUE != hFind)
	{		
		while(ModelNumLoadedWater<ModelNumWater)
		{
			if (FindFileData.cFileName[0] != '.')
			{
				pModelIDWater[ModelNumLoadedWater]=0;
				char sTmp2[256] = {0};
				char loadModelpathName[256] = {0};
				int tmpi=0;
				for(unsigned int i=0;i<strlen(FindFileData.cFileName);i++)
				{
					if(i<256)
					{
						if(FindFileData.cFileName[i]=='.')
							sTmp2[i]=0;
						else
							sTmp2[i]=FindFileData.cFileName[i];
					}
				}
				sprintf(loadModelpathName,"Data/Model/Waters/%s",sTmp2);
				pModelIDWater[ModelNumLoadedWater]=m_VBMD->Init(loadModelpathName);
				ModelNumLoadedWater=ModelNumLoadedWater+1;
			}
			if(!FindNextFile(hFind, &FindFileData))
				break;
		}
		FindClose(hFind);
	}



	ModelNum=GetPrivateProfileInt("Set","ModelNum",290,".\\Model.ini");
	pModelID=new int[ModelNum];

	sprintf(sTmp,"Data/Model/*.dds");
	hFind = ::FindFirstFile(sTmp, &FindFileData);
	if(INVALID_HANDLE_VALUE == hFind)
		MessageBox( NULL, "FindNoFile", "ERROR", MB_OK|MB_ICONEXCLAMATION );
	else
	{
		while(ModelNumLoaded<ModelNum)
		{
			if (FindFileData.cFileName[0] != '.')
			{
				pModelID[ModelNumLoaded]=0;
				char sTmp2[256] = {0};
				char loadModelpathName[256] = {0};
				int tmpi=0;
				for(unsigned int i=0;i<strlen(FindFileData.cFileName);i++)
				{
					if(i<256)
					{
						if(FindFileData.cFileName[i]=='.')
							sTmp2[i]=0;
						else
							sTmp2[i]=FindFileData.cFileName[i];
					}
				}
				sprintf(loadModelpathName,"Data/Model/%s",sTmp2);
				pModelID[ModelNumLoaded]=m_VBMD->Init(loadModelpathName);
				ModelNumLoaded=ModelNumLoaded+1;
			}
			if(!FindNextFile(hFind, &FindFileData))
				break;
		}
		FindClose(hFind);
	
	}

	sprintf(sTmp,"Data/Model/Alpha/*.dds");
	hFind = ::FindFirstFile(sTmp, &FindFileData);
	if(INVALID_HANDLE_VALUE != hFind)
	{		
		while(ModelNumLoaded<ModelNum)
		{
			if (FindFileData.cFileName[0] != '.')
			{
				pModelID[ModelNumLoaded]=0;
				char sTmp2[256] = {0};
				char loadModelpathName[256] = {0};
				int tmpi=0;
				for(unsigned int i=0;i<strlen(FindFileData.cFileName);i++)
				{
					if(i<256)
					{
						if(FindFileData.cFileName[i]=='.')
							sTmp2[i]=0;
						else
							sTmp2[i]=FindFileData.cFileName[i];
					}
				}
				sprintf(loadModelpathName,"Data/Model/Alpha/%s",sTmp2);
				pModelID[ModelNumLoaded]=m_VBMD->Init(loadModelpathName);
				ModelNumLoaded=ModelNumLoaded+1;
				ModelAlphaNumLoaded=ModelAlphaNumLoaded+1;
			}
			if(!FindNextFile(hFind, &FindFileData))
				break;
		}
		FindClose(hFind);
	}

	ballModelID=m_VBMD->Init("Data/ball");
	UImodelTest=m_VBMD->Init("Data/ta1");
}