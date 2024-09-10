	Filepath::Filepath(const tstring & full_path)
		: m_Path(EMPTY_STRING)
		, m_File(EMPTY_STRING)
	{
		int32 dotCounter(0);
		for(uint32 i = 0; i < full_path.size(); ++i)
		{
			if(full_path[i] == _T('.'))
			{
				++dotCounter;
			}
		}
		if(dotCounter > 1)
		{
			Logger::GetInstance()->Log(LogLevel::Error, 
				_T("Please don't use . in your filename (except for the file extension)"));
		}

		auto index = full_path.find_last_of('/');
		if(index == tstring::npos)
		{
			index = full_path.find_last_of('\\');
		}
		if(index != tstring::npos)
		{
			index += 1;
			m_Path = full_path.substr(0,index);
			m_File = full_path.substr(index, full_path.length() - index);
		}
		else
		{
			m_File = full_path;
		}
	}