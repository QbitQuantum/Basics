BOOL kull_m_string_suspectUnicodeString(IN PUNICODE_STRING pUnicodeString)
{
	int unicodeTestFlags = IS_TEXT_UNICODE_STATISTICS;
	return ((pUnicodeString->Length == sizeof(wchar_t)) && IsCharAlphaNumeric(pUnicodeString->Buffer[0])) || IsTextUnicode(pUnicodeString->Buffer, pUnicodeString->Length, &unicodeTestFlags);
}