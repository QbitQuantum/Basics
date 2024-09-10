	DynamicStringA StringToANSIString(const TempString &str)
	{
		UNICODE_STRING srcString;
		str.FillNTString(&srcString);
		DynamicStringA ret;
		size_t newLen = RtlUnicodeStringToAnsiSize(&srcString);
		if (!NT_SUCCESS(RtlUnicodeStringToAnsiString(ret.ToNTString(newLen), &srcString, FALSE)))
			ret.SetLength(0);
		else
			ret.UpdateLengthFromNTString();
		return ret;
	}