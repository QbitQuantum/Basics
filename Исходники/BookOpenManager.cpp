BOOL BookOpenManager::OpenArchiveBook()
{
    DebugPrintf(DLC_BOOKOPENMANAGER, "%s, %d, %s, %s START", __FILE__,  __LINE__, "BookOpenManager", __FUNCTION__);
	if(!m_pCurPage)
	{
		return FALSE;
	}

	CDisplay* display = CDisplay::GetDisplay();
	if(NULL == display)
	{
		return FALSE;
	}

	IFileContentsModel *pCurBookContent = NULL;
	if(S_FALSE == CFileContentsFactory::CreateFileContentsInstance(GetBookPath(),&pCurBookContent))
	{
		return FALSE;
	}

	if(NULL == pCurBookContent)
	{
		return FALSE;
	}

	char Password[128]={0};
	if(pCurBookContent->HasPassword())
	{
		if(GetFilePassword(m_pCurPage,m_iBookID,Password,128))
		{
			pCurBookContent->SetPassword(Password);
		}
		else
		{
			return TRUE;
		}
	}

	vector < CFileChapterInfo > ChapterList;
	if(!pCurBookContent->GetChapterList(ChapterList))
	{
		delete pCurBookContent;
		pCurBookContent = NULL;
		return FALSE;
	}

	int iChapterCount = ChapterList.size();
	FileListItem *pZipFileList = new FileListItem[iChapterCount];
	if(NULL == pZipFileList)
	{
		delete pCurBookContent;
		pCurBookContent = NULL;
		return FALSE;
	}

	INT iImageCount = 0;
	INT iAdjustIndex = 0;
	LPCSTR pExtension = NULL;
	LPCSTR pFileName = NULL;

	LPCSTR *pNameArray = new LPCSTR[iChapterCount];
	if(NULL == pNameArray)
	{
		delete pCurBookContent;
		pCurBookContent = NULL;

		delete[] pZipFileList;
		pZipFileList = NULL;
		return FALSE;
	}

	for(INT index= 0; index < iChapterCount; index++)
	{
		pExtension = ChapterList[index].GetChapterExName();
		if(DFC_Picture == GetFileCategoryForZipFile(pExtension))
		{
			pFileName = ChapterList[index].GetChapterPath();
			iAdjustIndex = AdjustFileList(pZipFileList, iImageCount, pNameArray, pFileName);

			pZipFileList[iAdjustIndex].uFileId = ChapterList[index].GetChapterId();
			pZipFileList[iAdjustIndex].eFileCategory = DFC_Picture;

			strncpy(pZipFileList[iAdjustIndex].pExtension, pExtension, 16);
			iAdjustIndex++;
			iImageCount++;
		}
	}

	DebugPrintf(DLC_BOOKOPENMANAGER, "BookOpenManager::OpenBook iImageCount %d\n", iImageCount);

	delete[] pNameArray;
	pNameArray = NULL;

	if(iChapterCount == iImageCount)
	{
		BookFileList * pZipBookList = new BookFileList();
		if(NULL == pZipBookList)
		{
			delete pCurBookContent;
			pCurBookContent = NULL;

			delete[] pZipFileList;
			pZipFileList = NULL;
			return FALSE;
		}

		pZipBookList->pFileList = pZipFileList;
		pZipBookList->iBookId= m_iBookID;
		pZipBookList->uLength = iImageCount;

		DkReaderPage *pReader = new DkReaderPage();
		if(NULL == pReader)
		{
			delete pCurBookContent;
			pCurBookContent = NULL;

			delete pZipBookList;
			pZipBookList = NULL;

			return FALSE;
		}

		if(!pReader->Initialize(SPtr<BookFileList>(pZipBookList), 0, TRUE,Password))
		{

			UIMessageBox messagebox(m_pCurPage, StringManager::GetStringById(CANNOT_OPEN_BOOK), MB_OK);
			messagebox.DoModal();

			delete pCurBookContent;
			pCurBookContent = NULL;

			delete pReader;
			pReader = NULL;
			return FALSE;
		}
		else
		{
			pReader->MoveWindow(0, 0, display->GetScreenWidth(), display->GetScreenHeight());
			CPageNavigator::Goto(pReader);
			delete pCurBookContent;
			pCurBookContent = NULL;
			return TRUE;
		}
	}
	else	//如果压缩包中含有非图片内容，则暂不支持！
    {
        UIMessageBox messagebox(m_pCurPage, StringManager::GetStringById(CANNOT_OPEN_BOOK), MB_OK);
        messagebox.DoModal();

		delete pCurBookContent;
		pCurBookContent = NULL;
		delete[] pZipFileList;
		pZipFileList = NULL;
		return FALSE;
    }
    DebugPrintf(DLC_BOOKOPENMANAGER, "%s, %d, %s, %s end", __FILE__,  __LINE__, "BookOpenManager", __FUNCTION__);
    return true;
}