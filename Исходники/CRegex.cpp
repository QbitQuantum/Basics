status_t CRegex::SetTo(const char* pattern, bool ignoreCase, bool fullWord,
					   bool backward)
{
	_Cleanup();
	return _Init(pattern, ignoreCase, fullWord, backward);
}