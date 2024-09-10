void accumulateValue(float* valuePtr, SyntaxErrorType errCode)
{
	float value = *valuePtr;
	//--------------------------------------------
	// Make sure the first character is a digit...
	if(calcCharCode(curChar) != CHR_DIGIT)
	{
		syntaxError(errCode);
		curToken = TKN_ERROR;
		return;
	}
	do
	{
		*tokenp = curChar;
		tokenp++;
		if(++digitCount <= MAX_DIGIT_COUNT)
			value = 10 * value + (curChar - '0');
		else
			countError = true;
		getChar();
	}
	while(calcCharCode(curChar) == CHR_DIGIT);
	*valuePtr = value;
}