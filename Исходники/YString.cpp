bool YString::GetSpecifier(wchar_t* specifier, int specifierSize, const wchar_t* str)
{
	Assert(NULL != str);
	Assert(NULL != specifier);

	swscanf_s(str, L"%s", specifier, specifierSize);

	return true;
Exit:
	return false;
}