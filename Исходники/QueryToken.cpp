void QueryToken::set(const UChar *inValue, int32_t inStart, int32_t inEnd, QueryToken::Types inType)
{
	if (mValue)
		delete [] mValue;
	if (inEnd == -1)
		inEnd = u_strlen(inValue);
	mValue = new UChar[inEnd + 1];
	u_strncpy(mValue, inValue, inEnd);
	mValue[inEnd] = 0;

	this->mStart = inStart;
	this->mEnd = inEnd;
	this->mType = inType;
}