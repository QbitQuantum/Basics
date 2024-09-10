int CLocateShellExtension::InsertMenuItems(HMENU hMenu,UINT nStartIndex,UINT idCmdFirst,UINT& nHighestUsedID)
{
	ODS("CShellExt::InsertMenuItems()");
	
	if (m_pDataObj==NULL)
		return 0;

	
	

	

	
	MENUITEMINFOW mii;
	mii.cbSize=sizeof(MENUITEMINFOW);
	mii.fMask=MIIM_ID|MIIM_TYPE;
	mii.fType=MFT_STRING;
	mii.dwTypeData=L"Files:";
	mii.wID=idCmdFirst;
    InsertMenuItemW(hMenu,nStartIndex++,TRUE,&mii);

	for (int i=0;i<m_aFiles.GetSize();i++)
	{
		mii.wID++;
		mii.dwTypeData=m_aFiles[i];
		InsertMenuItemW(hMenu,nStartIndex++,TRUE,&mii);
	}

	mii.wID++;
	mii.dwTypeData=L"Directories:";
	InsertMenuItemW(hMenu,nStartIndex++,TRUE,&mii);
	
	for (int i=0;i<m_aDirectories.GetSize();i++)
	{
		mii.wID++;
		mii.dwTypeData=m_aDirectories[i];
		InsertMenuItemW(hMenu,nStartIndex++,TRUE,&mii);
	}


	mii.wID++;
	mii.dwTypeData=L"Computers:";
	InsertMenuItemW(hMenu,nStartIndex++,TRUE,&mii);
	
	for (int i=0;i<m_aComputers.GetSize();i++)
	{
		mii.wID++;
		mii.dwTypeData=m_aComputers[i];
		InsertMenuItemW(hMenu,nStartIndex++,TRUE,&mii);
	}

	
	nHighestUsedID=mii.wID;
	
	return mii.wID-idCmdFirst+1;
}