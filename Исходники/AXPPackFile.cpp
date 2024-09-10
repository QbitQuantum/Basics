//文件自检功能
bool PackFile::selfCheck(SELFCHECK_CALLBACK callBack)
{
	if(0==m_hPakFile) 
	{
		setLastError(AXP_ERR_PARAM);
		return false;
	}

	//编辑模式错误
	if(m_fileHead.nEditFlag != 0)
	{
		setLastError(AXP_ERR_FILE_EDITMODE);
		return false;
	}

	//打开List文件
	IStream* pListStream = openFile(LIST_FILENAME);
	if(!pListStream) return false;

	//skip first line
	pListStream->skipLine();

	//read second line
	char szTempLine[MAX_PATH*4] = {0};
	int nLineSize = pListStream->readLine(szTempLine, MAX_PATH*4);
	int nFileCount = atoi(szTempLine);

	//记录已经检查过的HashNode索引
	std::set< unsigned int > setHashNode;
	//记录已经检查过的BlockNode索引
	std::set< unsigned int > setBlockNode;

	//逐行读文件
	int nFileListSize = 0;
	while (!pListStream->eof())
	{
		int nLineLength = pListStream->readLine(szTempLine, MAX_PATH*4);
		if(0 == nLineLength) 
		{
			pListStream->close();
			setLastError(AXP_ERR_FILE_FORMAT, "list file second line=0");
			return false;
		}

		//分析文件描述
		std::vector< std::string > vStringVec;
		convertStringToVector(szTempLine, vStringVec, "|", true, false);
		if(vStringVec.size() != 3) 
		{
			pListStream->close();
			setLastError(AXP_ERR_FILE_FORMAT, "list file=%s", szTempLine);
			return false;
		}

		//获得文件信息
		std::string& strFileName = vStringVec[0];
		unsigned int nFileSize, nFileCRC;
		sscanf(vStringVec[1].c_str(), "%08X", &(nFileSize));
		sscanf(vStringVec[2].c_str(), "%08X", &(nFileCRC));

		//读入文件
		IStream* pFileStream = openFile(strFileName.c_str());	//打开文件
		if(!pFileStream)
		{
			pListStream->close();
			return false;
		}

		unsigned int nStreamSize = pFileStream->size();
		if(nStreamSize != nFileSize)
		{
			pFileStream->close();
			pListStream->close();
			setLastError(AXP_ERR_FILE_FORMAT, "file=%s, sizedif(%d!=%d)", 
				strFileName.c_str(), nStreamSize, nFileSize);
			return false;
		}

		char* pTempBuf = new char[nStreamSize];
		if(nStreamSize != pFileStream->read(pTempBuf, nStreamSize))
		{
			pFileStream->close();
			pListStream->close();
			setLastError(AXP_ERR_FILE_READ, "file=%s", strFileName.c_str());
		}
		pFileStream->close(); pFileStream=0;

		//计算文件实际crc
		unsigned int  nStreamCRC;
		crcMemory32(pTempBuf, nStreamSize, nStreamCRC);
		delete[] pTempBuf; pTempBuf=0;

		if(nStreamCRC != nFileCRC)
		{
//			pFileStream->close();
			pListStream->close();
			setLastError(AXP_ERR_FILE_FORMAT, "file=%s, crcdif(%d!=%d)", 
				strFileName.c_str(), nStreamCRC, nFileCRC);
			return false;
		}

		//保存分析过的文件Hash和Block数据

		//得到Hash数据
		int nHashPos = getStringPosInHashTable(normaliseName(strFileName).c_str());
		setHashNode.insert(nHashPos);

		//得到Block数据
		unsigned int nBlockIndex = getHashNodeBlockIndex(m_hashTable[nHashPos]);
		setBlockNode.insert(nBlockIndex);

		nFileListSize++;
	};
	pListStream->close(); pListStream=0;

	//文件个数检查
	if(nFileListSize != nFileCount)
	{
		setLastError(AXP_ERR_FILE_FORMAT, "file countdif(%d!=%d)", nFileListSize, nFileCount);
		return false;
	}

	//得到(list)的Hash数据
	int nListFileHashPos = getStringPosInHashTable(LIST_FILENAME);
	//得到(list)的Block数据
	unsigned int nListFileBlockIndex = getHashNodeBlockIndex(m_hashTable[nListFileHashPos]);

	//检查是否有未引用的Hash数据
	for(int i=0; i<HASH_TABLE_SIZE; i++)
	{
		const FILE_HASHNODE& hashNode = m_hashTable[i];
		if(!getHashNodeExists(hashNode)) continue;

		if(setHashNode.find(i) != setHashNode.end()) continue;
		if(i==nListFileHashPos) continue;

		//未引用的Hash数据
		setLastError(AXP_ERR_FILE_FORMAT, "unref hashnode(%d)", i);
		return false;
	}

	//检查是否有未引用的BlockNode数据
	for(int i=0; i<(int)m_blockTable.size(); i++)
	{
		const FILE_BLOCKNODE& blockNode = m_blockTable[i];
		if(!getBlockNodeUsed(blockNode)) continue;
		if(setBlockNode.find(i) != setBlockNode.end()) continue;
		if(i==nListFileBlockIndex) continue;

		//未引用的Hash数据
		setLastError(AXP_ERR_FILE_FORMAT, "unref blocknode(%d)", i);
		return false;
	}

	return true;
}