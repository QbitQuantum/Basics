static void LettersFromSeq(const Seq &s, unsigned Letters[])
	{
	const unsigned uLength = s.Length();
	for (unsigned i = 0; i < uLength; ++i)
		{
		char c = s.GetChar(i);
		unsigned uLetter = CharToLetter(c);
		if (uLetter < 20)
			Letters[i] = uLetter;
		else
			Letters[i] = AX_X;
		}
	}