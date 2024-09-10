	string formatStringArgs( const char* pFormat, va_list argptr )
	{
		va_list argptrCount = argptr;
		va_list argptrFormat = argptr;

#pragma warning( disable : 4996 )
		const size_t len = _vsnprintf( nullptr, 0u, pFormat, argptrCount );
#pragma warning( default : 4996 )

		string str( len );
		_vsprintf_s_l(
			(char*)str.cStr(),
			str.getLength() + 1u,
			pFormat,
			nullptr,
			argptrFormat
		);

		return str;
	}