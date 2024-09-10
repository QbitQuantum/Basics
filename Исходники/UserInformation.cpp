//设置关系
tagCompanionInfo * CUserInformation::InsertCompanionInfo(IClientUserItem * pIClientUserItem, BYTE cbCompanion)
{
	//效验参数
	ASSERT(pIClientUserItem!=NULL);
	if (pIClientUserItem==NULL) return NULL;

	//用户搜索
	DWORD dwUserID=pIClientUserItem->GetUserID();
	tagCompanionInfo * pCompanionInfo=SearchCompanionInfo(dwUserID);

	//设置信息
	if (pCompanionInfo==NULL)
	{
		//创建对象
		pCompanionInfo=CreateCompanionItem();
		if (pCompanionInfo==NULL) return NULL;

		//设置信息
		pCompanionInfo->cbCompanion=cbCompanion;
		pCompanionInfo->dwGameID=pIClientUserItem->GetGameID();
		pCompanionInfo->dwUserID=pIClientUserItem->GetUserID();
		lstrcpyn(pCompanionInfo->szNickName,pIClientUserItem->GetNickName(),CountArray(pCompanionInfo->szNickName));
		lstrcpyn(pCompanionInfo->szUserNote,pIClientUserItem->GetUserNoteInfo(),CountArray(pCompanionInfo->szUserNote));

		//插入通知
		if (m_pIUserCompanionSink!=NULL) m_pIUserCompanionSink->OnCompanionInsert(pCompanionInfo);
	}
	else
	{
		//修改判断
		bool bModify=false;
		if (pCompanionInfo->cbCompanion!=cbCompanion) bModify=true;
		if ((bModify==false)&&(lstrcmp(pCompanionInfo->szNickName,pIClientUserItem->GetNickName())!=0)) bModify=true;
		if ((bModify==false)&&(lstrcmp(pCompanionInfo->szUserNote,pIClientUserItem->GetUserNoteInfo())!=0)) bModify=true;

		//修改判断
		if (bModify=false) return pCompanionInfo;

		//设置信息
		pCompanionInfo->cbCompanion=cbCompanion;
		pCompanionInfo->dwGameID=pIClientUserItem->GetGameID();
		pCompanionInfo->dwUserID=pIClientUserItem->GetUserID();
		lstrcpyn(pCompanionInfo->szNickName,pIClientUserItem->GetNickName(),CountArray(pCompanionInfo->szNickName));
		lstrcpyn(pCompanionInfo->szUserNote,pIClientUserItem->GetUserNoteInfo(),CountArray(pCompanionInfo->szUserNote));

		//更新通知
		if (m_pIUserCompanionSink!=NULL) m_pIUserCompanionSink->OnCompanionUpdate(pCompanionInfo);
	}

	//变量定义
	IStream * pIStreamSub=NULL;
	IStorage * pIStorageSub=NULL;
	IStorage * pIStorageRoot=NULL;

	//写入数据
	try
	{
		//构造名字
		WCHAR szStorageName[16]=L"";
		_snwprintf(szStorageName,CountArray(szStorageName),L"%ld",dwUserID);

		//工作目录
		TCHAR szDirectory[MAX_PATH]=TEXT("");
		CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

		//打开文件
		WCHAR szInfomationFile[MAX_PATH]=L"";
		_snwprintf(szInfomationFile,CountArray(szInfomationFile),L"%s\\%s",(LPCWSTR)(CT2CW(szDirectory)),INFORMATION_FILE);

		//打开文件
		StgOpenStorage(szInfomationFile,NULL,STGM_READWRITE|STGM_SHARE_EXCLUSIVE,0,0,&pIStorageRoot);
		if (pIStorageRoot==NULL) StgCreateDocfile(szInfomationFile,STGM_CREATE|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,0,&pIStorageRoot);

		//错误判断
		if (pIStorageRoot==NULL) throw TEXT("StgCreateDocfile Create pIStorageRoot Error");

		//打开存储
		pIStorageRoot->CreateStorage(szStorageName,STGM_WRITE|STGM_SHARE_EXCLUSIVE,0,0,&pIStorageSub);
		if (pIStorageSub==NULL) pIStorageRoot->CreateStorage(szStorageName,STGM_CREATE|STGM_WRITE|STGM_SHARE_EXCLUSIVE,0,0,&pIStorageSub);

		//错误处理
		if (pIStorageSub==NULL) throw TEXT("CreateStorage Create pIStorageSub Error");

		//创建数据
		pIStorageSub->CreateStream(STREAM_COMPANION,STGM_WRITE|STGM_SHARE_EXCLUSIVE,0,0,&pIStreamSub);
		if (pIStreamSub==NULL) pIStorageSub->CreateStream(STREAM_COMPANION,STGM_CREATE|STGM_WRITE|STGM_SHARE_EXCLUSIVE,0,0,&pIStreamSub);

		//错误处理
		if (pIStreamSub==NULL) throw TEXT("CreateStream Create pIStreamSub Error");

		//写入数据
		ULONG cbWriteCount=0L;
		pIStreamSub->Write(pCompanionInfo,sizeof(tagCompanionInfo),&cbWriteCount);

		//释放接口
		SafeRelease(pIStreamSub);
		SafeRelease(pIStorageSub);
		SafeRelease(pIStorageRoot);

		return pCompanionInfo;
	}
	catch (...)
	{
		//错误断言
		ASSERT(FALSE);

		//释放接口
		SafeRelease(pIStreamSub);
		SafeRelease(pIStorageSub);
		SafeRelease(pIStorageRoot);
	}

	return NULL;
}