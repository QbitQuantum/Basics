	Air::U1 FileMapping::OpenFile()
	{
		if(m_hFile==NULL){
			m_hFile	=	OpenFileMappingA(FILE_MAP_ALL_ACCESS,NULL,m_strProductName.c_str());
			if(m_hFile!=NULL){
				Lock(0,m_Info.uiFileSize);
			}
			
		}
		return m_hFile!=NULL;
	}