		file_logger(std::wstring path, std::wstring filename) : file_appender(path, filename), datemask_(_T("%Y-%m-%d %H:%M:%S")) {
			_tzset();
		}