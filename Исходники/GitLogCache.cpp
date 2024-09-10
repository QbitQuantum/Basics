int CLogCache::SaveCache()
{
	if (!m_bEnabled)
		return 0;

	int ret =0;
	BOOL bIsRebuild=false;

	if (this->m_HashMap.empty()) // is not sufficient, because "working copy changes" are always included
		return 0;

	if( this->m_GitDir.IsEmpty())
		return 0;

	if (this->m_pCacheIndex && m_pCacheIndex->m_Header.m_ItemCount == 0) // check for empty log list (issue #915)
		return 0;

	SLogCacheIndexFile *pIndex =  NULL;
	if(this->m_pCacheIndex)
	{
		pIndex = (SLogCacheIndexFile *)malloc(sizeof(SLogCacheIndexFile)
					+sizeof(SLogCacheIndexItem) * (m_pCacheIndex->m_Header.m_ItemCount) );
		if(pIndex ==NULL)
			return -1;

		memcpy(pIndex,this->m_pCacheIndex,
			sizeof(SLogCacheIndexFile) + sizeof(SLogCacheIndexItem) *( m_pCacheIndex->m_Header.m_ItemCount-1)
			);
	}

	this->CloseDataHandles();
	this->CloseIndexHandles();

	SLogCacheIndexHeader header;
	CString file = this->m_GitDir + INDEX_FILE_NAME;
	do
	{
		m_IndexFile = CreateFile(file,
						GENERIC_READ|GENERIC_WRITE,
						0,
						NULL,
						OPEN_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,
						NULL);

		if(m_IndexFile == INVALID_HANDLE_VALUE)
		{
			ret = -1;
			break;
		}

		file = m_GitDir + DATA_FILE_NAME;

		m_DataFile = CreateFile(file,
						GENERIC_READ|GENERIC_WRITE,
						0,
						NULL,
						OPEN_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,
						NULL);

		if(m_DataFile == INVALID_HANDLE_VALUE)
		{
			ret = -1;
			break;
		}


		{

			memset(&header,0,sizeof(SLogCacheIndexHeader));
			DWORD num=0;
			if((!ReadFile(m_IndexFile,&header, sizeof(SLogCacheIndexHeader),&num,0)) ||
				!CheckHeader(&header)
				)
			{
				RebuildCacheFile();
				bIsRebuild =true;
			}
		}
		if(!bIsRebuild)
		{
			SLogCacheDataFileHeader header;
			DWORD num=0;
			if((!ReadFile(m_DataFile,&header,sizeof(SLogCacheDataFileHeader),&num,0)||
				!CheckHeader(&header)))
			{
				RebuildCacheFile();
				bIsRebuild=true;
			}
		}

		if(bIsRebuild)
			header.m_ItemCount=0;

		SetFilePointer(m_DataFile,0,0,2);
		SetFilePointer(m_IndexFile,0,0,2);

		for (auto i = m_HashMap.begin(); i != m_HashMap.end(); ++i)
		{
			if(this->GetOffset((*i).second.m_CommitHash,pIndex) ==0 || bIsRebuild)
			{
				if((*i).second.m_IsDiffFiles && !(*i).second.m_CommitHash.IsEmpty())
				{
					LARGE_INTEGER offset;
					offset.LowPart=0;
					offset.HighPart=0;
					LARGE_INTEGER start;
					start.QuadPart = 0;
					SetFilePointerEx(this->m_DataFile,start,&offset,1);
					if (this->SaveOneItem((*i).second, (LONG)offset.QuadPart))
					{
						TRACE(_T("Save one item error"));
						SetFilePointerEx(this->m_DataFile,offset, &offset,0);
						continue;
					}

					SLogCacheIndexItem item;
					item.m_Hash = (*i).second.m_CommitHash;
					item.m_Offset=offset.QuadPart;

					DWORD num;
					WriteFile(m_IndexFile,&item,sizeof(SLogCacheIndexItem),&num,0);
					++header.m_ItemCount;
				}
			}
		}
		FlushFileBuffers(m_IndexFile);

		m_IndexFileMap = CreateFileMapping(m_IndexFile, NULL, PAGE_READWRITE,0,0,NULL);
		if(m_IndexFileMap == INVALID_HANDLE_VALUE)
		{
			ret =-1;
			break;
		}

		m_pCacheIndex = (SLogCacheIndexFile*)MapViewOfFile(m_IndexFileMap,FILE_MAP_WRITE,0,0,0);
		if(m_pCacheIndex == NULL)
		{
			ret = -1;
			break;
		}

		m_pCacheIndex->m_Header.m_ItemCount = header.m_ItemCount;
		Sort();
		FlushViewOfFile(m_pCacheIndex,0);

	}while(0);

	this->CloseDataHandles();
	this->CloseIndexHandles();

	if(pIndex)
		free(pIndex);
	return ret;
}