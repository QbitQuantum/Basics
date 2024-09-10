const char16 * FormatVL(const char16 * text, va_list ll)
{
	if (formatString16Position + FORMAT_STRING_MAX_LEN >= FORMAT_STRING_SIZE)
	{
		formatString16Position = 0;
	}
#if defined(_WIN32)
	int32 len = vswprintf((wchar_t *)&formatString16[formatString16Position], (wchar_t *)text, ll);
#else // MAC_OS & other nix systems
	int32 len = vswprintf((wchar_t *)&formatString16[formatString16Position], FORMAT_STRING_MAX_LEN, (wchar_t *)text, ll);
#endif
	
	formatString16Position += (len + 1);
	return &formatString16[formatString16Position - (len + 1)];
}