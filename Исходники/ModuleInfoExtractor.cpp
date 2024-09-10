	const NEExportable::ModuleHeader NE_DLL &ModuleInfoExtractor::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T("ModuleInfoExtractor");
			_header.getDeveloper() = _T("kniz");
			_header.setRevision(1);
			_header.getComment() = _T("0번. 추출할 모듈의 ScriptCode \n1번. 빼내려는 정보의 종류(0:이름, 1:개발자명, 2:개정번호, 3:배포날짜, 4:버전, 5:코멘트, 6:연락처");
			_header.getVersion()  = _T("0.0.1a");
			_header.getReleaseDate() = _T("2013-10-05");
			_header.getModuleDependencies().create(0);
			_header.setMaxErrorCodeCount(0);
		}

		return _header;
	}