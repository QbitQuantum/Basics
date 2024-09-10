void CChatPrefs::LoadChatAliases(CString ConfigFile)
{
	CFile File;

	
	if(File.Open(ConfigFile, CFile::modeRead))
	{
		char* buffer;
		buffer = new char[File.GetLength() + 1];

		UINT byteread = File.Read(buffer, File.GetLength());
		buffer[File.GetLength()] = '\0';

		CString Data = buffer;
		
		// Parse the data
		CString ParseList;
		
		while (Data.Find("\r\n") != -1)
		{
			int pos = Data.Find("\r\n");
			
			CString LineText;
			LineText = Data.Left(pos + 2);
			Data = Data.Right(Data.GetLength() - pos - 2);
		
			int epos = LineText.Find('=');
			if (epos != -1)
			{
				LineText = LineText.Right(LineText.GetLength() - epos - 1);
				ParseList += LineText;
			}
		}
		
		// Put list of aliases in map
		m_pChat->m_AliasMap.RemoveAll();
	
		int pos  = ParseList.Find("\r\n");
		int lpos = 0;
		CString command;

		while (pos != -1)
		{
			command = ParseList.Left(pos);
			ParseList = ParseList.Right(ParseList.GetLength() - pos - 2);
			pos = ParseList.Find("\r\n");		

			if (command.Find(' ') != -1)
				m_pChat->m_AliasMap.SetAt(command.Left(command.Find(' ')), command.Right(command.GetLength() - command.Find(' ') - 1));
		}
		
		delete [] buffer;
		File.Abort();
	}
}