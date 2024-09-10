/**
* CStringA::Format
* @date Modified Mar 02, 2006
*/
void CStringA::Format(const wchar_t* wszFormat, ...)
{
	// Get arguments
	va_list vaList;
	va_start(vaList, wszFormat);

	// Determine size of full string.
	int nSize = _vscwprintf(wszFormat, vaList);

	// Allocate buffer.
	wchar_t* wszBuffer = new wchar_t[nSize+1];
	memset(wszBuffer, 0, sizeof(wchar_t) * (nSize+1));

	// Save string.
	vswprintf(wszBuffer, wszFormat, vaList);
	CStringW str;
	str.m_strTheString = wszBuffer;

	// Cleanup buffer
	delete [] wszBuffer;

	// Cleanup args.
	va_end(vaList);

	// Use string conversion to save the final string
	(*this) = str;
}