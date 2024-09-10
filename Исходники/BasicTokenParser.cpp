//------------------------------------------------------------------------------
TCHAR FBasicTokenParser::GetLeadingChar()
{
	// if the parser is in a bad state, then don't continue parsing (who 
	// knows what will happen!?)... return a char signaling the end-of-stream
	if (!IsValid())
	{
		return 0;
	}

	TCHAR TrailingCommentNewline = 0;
	for (;;)
	{
		bool MultipleNewlines = false;

		TCHAR c;

		// Skip blanks.
		do
		{
			c = GetChar();

			// Check if we've encountered another newline since the last one
			if (c == TrailingCommentNewline)
			{
				MultipleNewlines = true;
			}
		} while (IsWhitespace(c));

		if (c != TEXT('/') || PeekChar() != TEXT('/'))
		{
			return c;
		}

		// Clear the comment if we've encountered newlines since the last comment
		if (MultipleNewlines)
		{
			ClearCachedComment();
		}

		// Record the first slash.  The first iteration of the loop will get the second slash.
		PrevComment += c;

		do
		{
			c = GetChar(true);
			if (c == 0)
				return c;
			PrevComment += c;
		} while (!IsEOL(c));

		TrailingCommentNewline = c;

		for (;;)
		{
			c = GetChar();
			if (c == 0)
				return c;
			if (c == TrailingCommentNewline || !IsEOL(c))
			{
				UngetChar();
				break;
			}

			PrevComment += c;
		}
	}
}