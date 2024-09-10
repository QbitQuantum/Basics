	//	---------------------------------------------------------------------------------
	//	설명	:	모듈의 헤더를 내보낸다. 헤더는 클래스에 이미 정의되어서 컴파일된다.
	//	동작조건:
	//	메모	:	헤더는 Static으로 되어있다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//				2011-07-09	이태훈	변경		
	//					:	노드엔진의 헤더를 추가했고, 데이터를 노드엔진 헤더에 통합했다.
	//						처음에는 컴파일시 정한 디폴트값이 들어가고, 이 후 INI로부터 
	//						데이터를 가져온다.
	//	---------------------------------------------------------------------------------
	const NEExportable::ModuleHeader NE_DLL &Kernal::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			//	디폴트 값으로 할당:
			//		식별자 할당:
			_header.getName() = _T(_NAME);
			_header.getDeveloper() = _T(_DEVELOPER);
			_header.setRevision(_REVISION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getVersion()  = _T(_VERSION);
			_header.getComment() = _T(_COMMENT);
			_header.setMaxErrorCodeCount(0);
			//_header.getModuleDependencies() = _T(_DEPENDENCIES );
			//_header.version_compatibilities = _T(_VERSION_COMPATIBILITIES);
		}

		return _header;
	}	