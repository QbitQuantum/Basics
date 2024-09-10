////////////////////////////////////////////////////////////////////////
// 描    述:  统计当前目录下的文件和子目录，并返回数量，需要指定条件m_sFilter
// 作    者:  邵凯田
// 创建时间:  2011-11-18 11:32
// 参数说明:  void
// 返 回 值:  文件和子目录的数量
//////////////////////////////////////////////////////////////////////////
int SDir::count()
{
	m_fileList.clear();
	m_fileAttrList.clear();
	
#ifdef WIN32
	if(m_sFilter == "")
		m_sFilter = "*";
	SString str = m_sDirName+"/"+m_sFilter;
	void *m_pNextInfo = new WIN32_FIND_DATA;
	HANDLE h = ::FindFirstFile(str.data(), (WIN32_FIND_DATA*) m_pNextInfo);
	while(h != INVALID_HANDLE_VALUE)
	{
		SString *pStr=new SString(((LPWIN32_FIND_DATA) m_pNextInfo)->cFileName);			
		m_fileList.append(pStr);
		SString *pAttr=new SString();
		DWORD attr = ((LPWIN32_FIND_DATA) m_pNextInfo)->dwFileAttributes;
		if((attr & FILE_ATTRIBUTE_DIRECTORY) != 0)
			*pAttr = "isdir=1;";//是目录
		else
			*pAttr = "isdir=0;";//不是目录
		m_fileAttrList.append(pAttr);
		BOOL bFile = ::FindNextFile(h, (LPWIN32_FIND_DATA) m_pNextInfo);
		if(bFile == FALSE)
			break;
	}
	if(h != INVALID_HANDLE_VALUE)
		FindClose(h);
	delete m_pNextInfo;
#else
	DIR *dir;
	struct dirent *ptr;
	SString sTemp;
	dir=opendir(m_sDirName.data());
	if(dir == NULL)
		return 0;//可能目录不存在，不能readdir
	while((ptr = readdir(dir)) != 0)
	{
		SString str=m_sFilter;
		str.replace("*","");
		SString *pStr=new SString(ptr->d_name);			
		if(str.length() > 0 && pStr->find(str) < 0)
		{
			delete pStr;
			continue;
		}

		SString *pAttr=new SString();
		struct   stat   st;
		sTemp.sprintf("%s/%s",m_sDirName.data(),pStr->data());
		stat(sTemp.data(),&st);
		if(S_ISDIR(st.st_mode))
			*pAttr = "isdir=1;";//是目录
		else
			*pAttr = "isdir=0;";//不是目录
		m_fileAttrList.append(pAttr);

		m_fileList.append(pStr);
	}
	closedir(dir);
#endif
	return m_fileList.count();
}