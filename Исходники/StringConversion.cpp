	void tstring2string(const tstring& src, std::string& dst)
	{
#ifdef UNICODE
		{
			char* newStr = "";
			int _len = 0;
			if (!src.empty()) {
				_len = WideCharToMultiByte(CP_UTF8, 0, src.c_str(),
					src.length(), NULL,
					0, NULL, NULL);
				newStr = new char[_len + 1];

				WideCharToMultiByte(CP_UTF8, 0, src.c_str(),
					src.length(), newStr,
					_len, NULL, NULL);

				newStr[_len] = 0; //Null terminator
			}
			dst = newStr;
			delete newStr;
		}
#else
		dst = src;
#endif
	}