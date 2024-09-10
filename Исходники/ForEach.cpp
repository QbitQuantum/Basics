	const NEExportable::ModuleHeader &ForEach::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("ForEach");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("0번. For를 돌 대상\n1번. OUT 루프를 돈 Count(index가 아님)\n2번. 매 대상마다 실행할 Actions");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("2013-10-06");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(0);
		}

		return _header;
	}