MojErr MojDbTextUtils::strToUnicode(const MojString& src, UnicodeVec& destOut)
{
	MojErr err = destOut.resize(src.length() * 2);
	MojErrCheck(err);
	MojInt32 destCapacity = 0;
	MojInt32 destLength = 0;
	do {
		UChar* dest = NULL;
		err = destOut.begin(dest);
		MojErrCheck(err);
		destCapacity = (MojInt32) destOut.size();
		UErrorCode status = U_ZERO_ERROR;
		u_strFromUTF8(dest, destCapacity, &destLength, src.data(), (MojInt32) src.length(), &status);
		if (status != U_BUFFER_OVERFLOW_ERROR)
			MojUnicodeErrCheck(status);
		err = destOut.resize(destLength);
		MojErrCheck(err);
	} while (destLength > destCapacity);

	return MojErrNone;
}