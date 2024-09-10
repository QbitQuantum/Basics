	void ICUUnicodeSupport::_toUpperCase<2>(StringHolder<2> _str)
	{
		if(!_str.empty())
		{
			uint16_t* buf = &_str[0];
			int32_t len = _str.length();
			int32_t ofs = 0, ofs2 = 0;
			while(ofs != len)
			{
				UChar32 c;
				U16_NEXT(buf, ofs, len, c);
				c = u_toupper(c);
				U16_APPEND_UNSAFE( buf, ofs2, c);
			}
		}
	}