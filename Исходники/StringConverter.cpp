	void StringConverter::ToSingle (const wstring &wstr, string &str, bool noThrow)
	{
		try
		{
			mbstate_t mbState;
			Memory::Zero (&mbState, sizeof (mbState));
			const wchar_t *src = wstr.c_str();

			size_t size = wcsrtombs (nullptr, &src, 0, &mbState);
			if (size == (size_t) -1)
				throw StringConversionFailed (SRC_POS, wstr);

			vector <char> buf (size + 1);
			Memory::Zero (&mbState, sizeof (mbState));

			if ((size = wcsrtombs (&buf[0], &src, buf.size(), &mbState)) == (size_t) -1)
				throw StringConversionFailed (SRC_POS, wstr);

			str.clear();
			str.insert (0, &buf.front(), size);
			Memory::Erase (&buf.front(), buf.size());
		}
		catch (...)
		{
			if (!noThrow)
				throw;
		}
	}