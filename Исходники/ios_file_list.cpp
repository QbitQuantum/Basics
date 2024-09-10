void CIOSFileList::OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	CIOSDirectoryTree::m_askIsTransPng = true;
	CIOSDirectoryTree::m_askIsTransPlist = true;
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	UINT uFileCount = 0;
	int iItem = GetNextItem(-1,LVNI_SELECTED);
	std::vector<std::wstring> names;
	std::vector<int> items;
	while (iItem != -1)
	{
		std::wstring name = this->GetItemText(iItem, 0).GetString();
		std::wstring path = m_indexList->GetPathByHTreeItem(m_hTreeItem) + name;
		if (m_indexList->IsFolderItem(path, true))
		{
			iItem = GetNextItem(iItem,LVNI_SELECTED);
			continue;
		}
		++uFileCount;
		names.push_back(name);
		items.push_back(iItem);
		iItem = GetNextItem(iItem,LVNI_SELECTED);
	}

	UINT uBuffSize = sizeof(FILEGROUPDESCRIPTOR) + (uFileCount) * sizeof(FILEDESCRIPTOR);
	HGLOBAL hFileDescriptor = GlobalAlloc (GHND | GMEM_SHARE, uBuffSize);        
	if(hFileDescriptor)
	{
		FILEGROUPDESCRIPTOR* pGroupDescriptor = (FILEGROUPDESCRIPTOR*) GlobalLock ( hFileDescriptor );
		if(pGroupDescriptor)
		{
			FILEDESCRIPTOR* pFileDescriptorArray = (FILEDESCRIPTOR*)((LPBYTE)pGroupDescriptor + sizeof(UINT));
			pGroupDescriptor->cItems = uFileCount;
			for (size_t index = 0; index < names.size(); ++index)
			{          
				ZeroMemory(&pFileDescriptorArray[index], sizeof(FILEDESCRIPTOR));
				pFileDescriptorArray[index].dwFlags = FD_FILESIZE|FD_ATTRIBUTES;

				int size = 0;
				for (size_t i = 0; i < m_itemDatas.size(); ++i)
				{
					if (m_itemDatas[i])
					{
						if (!wcscmp(m_itemDatas[i]->itemData[0]->strValue, names[index].c_str()))
						{
							size = m_itemDatas[i]->itemData[2]->intValue;
							break;
						}
					}
				}
				pFileDescriptorArray[index].nFileSizeLow = size;
				pFileDescriptorArray[index].nFileSizeHigh = 0;
				pFileDescriptorArray[index].dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
				lstrcpy ( pFileDescriptorArray[index].cFileName, names[index].c_str());	
			}
			GlobalUnlock ( hFileDescriptor ); 
		}
	}
	else
	{
		GlobalFree ( hFileDescriptor );
	}


	CHOleDataSource dragDataSource;
	dragDataSource.SetAssociat(items, m_indexList);
	FORMATETC etcDescriptor = { RegisterClipboardFormat(CFSTR_FILEDESCRIPTOR), NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	dragDataSource.CacheGlobalData( RegisterClipboardFormat(CFSTR_FILEDESCRIPTOR), hFileDescriptor, &etcDescriptor );

	FORMATETC etcContents = {RegisterClipboardFormat(CFSTR_FILECONTENTS), NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	dragDataSource.DelayRenderFileData(RegisterClipboardFormat(CFSTR_FILECONTENTS), &etcContents);

	DROPEFFECT dwEffect = dragDataSource.DoDragDrop( DROPEFFECT_COPY | DROPEFFECT_MOVE );
	if(dwEffect == DROPEFFECT_NONE )
	{
		GlobalFree( hFileDescriptor );
	} 

	CIOSDirectoryTree::m_askIsTransPng = true;
	CIOSDirectoryTree::m_askIsTransPlist = true;
	*pResult = 0;
}