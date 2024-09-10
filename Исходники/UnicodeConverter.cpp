/*----------------------------------------------------------------------------------------------
	This method uses an ICU function to convert a string from UTF-8 to UTF-16.

	Assumptions:
		If sourceLen is -1, it will be computed (by ICU)

	Exit conditions:
		<text>

	Parameters:
		<text>

	Return value:
		The number of characters required to store the fully-converted string
			(which may be greater than targetLen)
----------------------------------------------------------------------------------------------*/
int UnicodeConverter::Convert(const char* source, int sourceLen,
	UChar* target, int targetLen)
{
	UErrorCode status = U_ZERO_ERROR;
	int32_t spaceRequiredForData;

	u_strFromUTF8(target, targetLen, &spaceRequiredForData, source, sourceLen, &status);

	if (U_FAILURE(status) && status != U_BUFFER_OVERFLOW_ERROR)
		throw std::runtime_error("Unable to convert from UTF-8 to UTF-16");

	return spaceRequiredForData;
}