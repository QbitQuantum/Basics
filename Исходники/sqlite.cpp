		void					sqlite_db::pragma_synchronous(int mode)
		{
			wchar_t buffer[64];
			_itow_s(mode,buffer,10);
			query(wstring(L"pragma synchronous = ")+buffer+L";");
		}