	const NEExportable::ModuleHeader NE_DLL &WNDDomainManipulator::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T( _NAME );
			_header.getDeveloper() = _T( _DEVELOPER );
			_header.setRevision(_REVISION);
			_header.getComment() = _T( _COMMENT );
			_header.getVersion()  = _T( _VERSION );
			_header.getReleaseDate() = _T( _DATE );
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(WNDDomainManipulator::ERROR_CODE_END - 1);
			NETStringSet& args = _header.getArgumentsComments();
			args.create(_KEY_NUMBER);
			args.push(_KEY_COMMENT_1);
			args.push(_KEY_COMMENT_2);
			args.push(_KEY_COMMENT_3);
			args.push(_KEY_COMMENT_4);
			args.push(_KEY_COMMENT_5);
			args.push(_KEY_COMMENT_6);
			args.push(_KEY_COMMENT_7);
		}

		return _header;
	}