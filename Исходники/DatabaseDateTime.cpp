		std::wstring Format( const DateTimeType & dateTime, const std::wstring & format )
		{
			wchar_t buffer[Utils::DATE_TIME_MAX_SIZE + 1] = { 0 };
			std::tm tm = boost::posix_time::to_tm( dateTime );
			size_t length = wcsftime( buffer, Utils::DATE_TIME_MAX_SIZE, format.c_str(), &tm );
			assert( length < Utils::DATE_TIME_MAX_SIZE );
			return std::wstring( buffer, buffer + length );
		}