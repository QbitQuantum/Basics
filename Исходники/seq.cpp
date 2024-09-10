void Seq::ToFASTAFile(TextFile &File) const
	{
	File.PutFormat(">%s\n", m_ptrName);
	unsigned uColCount = Length();
	for (unsigned n = 0; n < uColCount; ++n)
		{
		if (n > 0 && n%60 == 0)
			File.PutString("\n");
		File.PutChar(at(n));
		}
	File.PutString("\n");
	}