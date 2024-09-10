//! 递归函数，把一个节点的所有内容写入指定的存盘位置
DWORD UpdateFolder::WriteDataToDir(LPCSTR pDirPath, tagDirectory &Directory)
{
	DWORD dwLoadFileNum = 0;
	//! 创建当前目录
	string strCurrDir(pDirPath);
	strCurrDir.append("\\");
	MakeSureDirectoryPathExists(strCurrDir.c_str());

	//! 创建当前文件
	list<CUpdateFile>::iterator iteFile = Directory.listFile.begin();
	for (; Directory.listFile.end() != iteFile; ++iteFile)
	{
		if(iteFile->WriteDataToPath(strCurrDir.c_str()))
			++ dwLoadFileNum;
	}

	//! 递归调用创建子目录
	list<tagDirectory>::iterator iteDir = Directory.listDir.begin();
	for (; Directory.listDir.end() != iteDir; ++iteDir)
	{
		dwLoadFileNum += WriteDataToDir((strCurrDir + iteDir->szName).c_str(), *iteDir);
	}

	return dwLoadFileNum;
}