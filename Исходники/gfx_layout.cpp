	static size_t AppendToBuffer(UChar *buff, const UChar *buffer_last, WChar c)
	{
		/* Transform from UTF-32 to internal ICU format of UTF-16. */
		int32 length = 0;
		UErrorCode err = U_ZERO_ERROR;
		u_strFromUTF32(buff, buffer_last - buff, &length, (UChar32*)&c, 1, &err);
		return length;
	}