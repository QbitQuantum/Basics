//==========================================================================
// SkipComment
//	Reads stuff until a newline is found.
//==========================================================================
void SkipComment()
{
	int ch = FGetC();
	bool seq = false;
	
	if(ch == '\n') return; // Comment ends right away.
	if(ch != '>') // Single-line comment?
	{
		while(FGetC() != '\n' && !endOfSource) {}
	}
	else // Multiline comment?
	{
		while(!endOfSource)
		{
			ch = FGetC();
			if(seq) 
			{
				if(ch == '#') break;
				seq = false;
			}
			if(ch == '<') seq = true;
		}
	}
}