static bool PSR_FindAndEnterBlock(FScanner &sc, const char* keyword)
{
	// Finds a block with a given keyword and then enter it (opening brace)
	// Should be closed with PSR_FindEndBlock
	while(sc.GetToken())
	{
		if(sc.TokenType == '}')
		{
			sc.UnGet();
			return false;
		}

		sc.TokenMustBe(TK_StringConst);
		if(!sc.Compare(keyword))
		{
			if(!sc.CheckToken(TK_StringConst))
				PSR_SkipBlock(sc);
		}
		else
		{
			sc.MustGetToken('{');
			return true;
		}
	}
	return false;
}