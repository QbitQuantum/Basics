bool CBrowseDir::SetInitDir(const char *dir) 
{ 
	//先把dir转换为绝对路径 
	if (_fullpath(m_szInitDir,dir,_MAX_PATH) == NULL) 
		return false; 
	//判断目录是否存在 
	if (_chdir(m_szInitDir) != 0) 
		return false; 
	//如果目录的最后一个字母不是'\',则在最后加上一个'\' 
	int len=strlen(m_szInitDir); 
	if (m_szInitDir[len-1] != '\\') 
		strcat(m_szInitDir,"\\");  
	return true; 
} 