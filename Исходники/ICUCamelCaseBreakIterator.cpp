void FICUCamelCaseBreakIterator::TokenizeString(TArray<FToken>& OutTokens)
{
	OutTokens.Empty(String.Len());

	FICUTextCharacterIterator CharIter(String);
	for(CharIter.setToStart(); CharIter.current32() != FICUTextCharacterIterator::DONE; CharIter.next32PostInc())
	{
		const UChar32 CurrentChar = CharIter.current32();

		ETokenType TokenType = ETokenType::Other;
		if(u_isULowercase(CurrentChar))
		{
			TokenType = ETokenType::Lowercase;
		}
		else if(u_isUUppercase(CurrentChar))
		{
			TokenType = ETokenType::Uppercase;
		}
		else if(u_isdigit(CurrentChar))
		{
			TokenType = ETokenType::Digit;
		}

		const int32 CharIndex = CharIter.InternalIndexToSourceIndex(CharIter.getIndex());
		OutTokens.Emplace(FToken(TokenType, CharIndex));
	}

	OutTokens.Emplace(FToken(ETokenType::Null, String.Len()));

	// There should always be at least one token for the end of the string
	check(OutTokens.Num());
}