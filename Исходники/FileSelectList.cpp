bool CFileSelectList::AddFileItem(LPITEMIDLIST pFullIDLS,int nOption)
{
	bool res = false;

	SHFILEINFO fileInfo={0};
	if(SHGetFileInfo((LPCTSTR)pFullIDLS,0,&fileInfo,sizeof(fileInfo),SHGFI_PIDL |SHGFI_DISPLAYNAME|SHGFI_ATTRIBUTES|SHGFI_ICON|SHGFI_SMALLICON) != 0)
	{
		if(fileInfo.dwAttributes & SFGAO_FILESYSTEM)
		{

			bool bIsFile = false;
			if(fileInfo.dwAttributes & SFGAO_FOLDER)//判断是否是文件系统对象文件夹,排除zip文件
			{
				if(fileInfo.dwAttributes & SFGAO_STREAM) 
				{
					int nSysID = GetWindowsSystemID();
					if(nSysID == WINDOWS_XP || nSysID == WINDOWS_VISTA || nSysID == WINDOWS_2003)
					{
							bIsFile = true;//zip文件
					}
				}
			}
			else
			{
				bIsFile = true;
			}

			if(!bIsFile) //是文件夹，但不是.zip文件
			{
				IShellFolder *pIParentFolder,*pICurFolder;
				LPITEMIDLIST pLocalIDLS;

				if(nOption & UNIFOLDER_PIG)//作为整体归档
				{
					goto PIG_FILE;
				}
				else//归档下面的文件
				{
					if(S_OK == SHBindToParent(pFullIDLS,IID_IShellFolder,(void**)&pIParentFolder,(LPCITEMIDLIST*)&pLocalIDLS))
					{
						if(S_OK == pIParentFolder->BindToObject(pLocalIDLS,NULL,IID_IShellFolder,(void**)&pICurFolder))
						{
							IEnumIDList* pIEnum;
							SHCONTF enumFlag = (nOption&FOLDER_RECURSIVEG_PIG)?(SHCONTF_FOLDERS|SHCONTF_NONFOLDERS):SHCONTF_NONFOLDERS;
							if(S_OK == pICurFolder->EnumObjects(NULL,enumFlag,&pIEnum))
							{
								for(HRESULT call_res = pIEnum->Next(1,&pLocalIDLS,NULL);call_res == S_OK;call_res = pIEnum->Next(1,&pLocalIDLS,NULL))
								{
									LPITEMIDLIST pFullChildIDLST = ILCombine(pFullIDLS,pLocalIDLS);
									if(pFullChildIDLST != NULL)
									{
										AddFileItem(pFullChildIDLST,nOption);
										ILFree(pFullChildIDLST);
									}

									CoTaskMemFree(pLocalIDLS);
								}
								pIEnum->Release();
							}
							pICurFolder->Release();
						}
						pIParentFolder->Release();
					}
				}

			}
			else //is file
			{
PIG_FILE:
				TCHAR tcbufPath[MAX_PATH];
				if(SHGetPathFromIDList(pFullIDLS,tcbufPath))
				{
					if(!IsAlreayIn(FilePath2Url(CString(tcbufPath))))
					{
						CString strPathFolder,strFName,strDriver,strExt;
						SplitFilePath(CString(tcbufPath),strPathFolder,strDriver,strFName,strExt);

						LVITEM lvit = {0};
						lvit.mask = LVIF_IMAGE|LVIF_TEXT;
						lvit.iItem = GetItemCount();
						lvit.pszText = (LPWSTR)(LPCTSTR)strFName;
						lvit.cchTextMax = strFName.GetLength();

						int iImg;
						if(!m_iSys2Self.Lookup(fileInfo.iIcon,iImg))
						{

							//CImageList *pImgLs = GetImageList(LVSIL_SMALL);
							iImg = GetImageList(LVSIL_SMALL)->Add(fileInfo.hIcon);
							m_iSys2Self.SetAt(fileInfo.iIcon,iImg);
						}

						lvit.iImage = iImg;
						int iItem = InsertItem(&lvit);
						//SetItem(iItem,1,LVIF_TEXT,strPathFolder+L"\\",0,0,0,0);
						SetItemText(iItem,1,tcbufPath);

						ItemDataType* pItemData = new ItemDataType;
						pItemData->strItemUrl = FilePath2Url(tcbufPath);
						SetItemData(iItem,(DWORD_PTR)pItemData);

					}
				}
			}
		}
		DestroyIcon(fileInfo.hIcon);
	}
	
	return res;
}