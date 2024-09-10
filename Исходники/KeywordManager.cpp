void KeywordManager::WriteKeywordDataToFile()
{
	CFile keyword_data_file;

	BOOL ret=MakeSureDirectoryPathExists("Keyword Files\\");

	for(UINT i=0; i<v_all_project_keywords.size(); i++)
	{
		BOOL open_write = FALSE;

		char filename[256+1];
		strcpy(filename, "Keyword Files\\");

		CString project = v_all_project_keywords[i].m_project_name.c_str();
		project.Replace('\\','_');			// replace the backslash with _
		project.Replace('\'', '_');		// replace the single quote "'" with _
		project.Replace(' ', '_');
		project.Replace('-', '_');
		project.Replace('&', '_');
		project.Replace('!', '_');
		project.Replace('$', '_');
		project.Replace('@', '_');
		project.Replace('%', '_');
		project.Replace('(', '_');
		project.Replace(')', '_');
		project.Replace('+', '_');
		project.Replace('~', '_');
		project.Replace('*', '_');
		project.Replace('.', '_');
		project.Replace(',', '_');
		project.Replace('?', '_');
		project.Replace(':', '_');
		project.Replace(';', '_');
		project.Replace('"', '_');
		project.Replace('#', '_');
		strcat(filename, project);
		strcat(filename, ".kwd");
		
		open_write = keyword_data_file.Open(filename,CFile::typeBinary|CFile::modeCreate|CFile::modeWrite|CFile::shareDenyNone);

		if(open_write==TRUE)
		{
			int buf_len = v_all_project_keywords[i].GetBufferLength();
			char *buf = new char[buf_len];

			v_all_project_keywords[i].WriteToBuffer(buf);

			keyword_data_file.Write(buf, buf_len);

			delete [] buf;

			keyword_data_file.Close();
		}
	}
}