//------------------------------------------
size_t CFS_Sqlite::WriteUTF8(const wchar* string, FSFILE *fp)
{
	if (!string || !*string) return 0;

	// if not unicode
#ifndef UNICODE
	return Write(string, 1, strlen(string), fp);
#else

	unsigned int inputLen = wstrlen(string);
	unsigned char *target;
	target = new unsigned char[inputLen*4+1]; // make buffer long enough
	UErrorCode status = U_ZERO_ERROR;
	int32_t     len;

	//// set up the converter
	UConverter *conv = ucnv_open("utf-8", &status);
	assertd(U_SUCCESS(status)!=0, "Failed to open utf-8 converter!");

	//// convert 
	len = ucnv_fromUChars(conv, (char*)target, inputLen*4, string, -1, &status);
	assertd(U_SUCCESS(status)!=0, "Failed to convert string to utf-8!");

	//// write to file
	size_t wrlen = Write(target, 1, len, fp);

	//// close and clean
	delete[] target;
	ucnv_close(conv);

	return wrlen;
#endif
}