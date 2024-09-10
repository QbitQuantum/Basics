BOOL static getField(ifstream& fin, CString& marker, CString& contents)
{
	static BOOL bNextLineIsBlank=FALSE;
	if(bNextLineIsBlank)
	{
		bNextLineIsBlank=FALSE;
		marker = "BLANKLINE";
		contents ="";
		return TRUE;
	}

	ASSERTX(fin.is_open());

	const int kBuffSize = 5000;	// CURRENTLY MAX FIELD SIZE TOO!

	CString sField;
	LPTSTR buff = sField.GetBuffer(kBuffSize+2);
	LPTSTR start_buff = buff;

	fin.eatwhite();
	char* b = buff;
	BOOL bFoundBlank = FALSE;
	do
	{
		fin.getline(b, kBuffSize - (b-buff), '\n');
		b += fin.gcount();
		if(fin.gcount())
		{
			*(b-1) = '\n'; // put a carriage return in place of the null terminator
			*b = '\0';		// null terminate in case the next getline fails
		}
		while(fin.peek() == '\n') // keep swallowing blank lines until we see what's at the end of them
		{
			fin.get(); // swallow the \n;
			if(fin.peek() == '\\')	 // if the blanks are followed by a record, then this constitutes a true blank line
			{
				bFoundBlank=TRUE;
				break;
			}
		}
	} while (!bFoundBlank && fin.good() && fin.gcount() && fin.peek() != '\\');

	bNextLineIsBlank = bFoundBlank; // will be used on the next call

	if( (kBuffSize-1) <= (b-buff))	// to long (and thus fin.gcount() == 0)
	{
		CString s;
		s.Format("The interlinear file appears to have a line which is longer than the maximum of %d characters which csCleanITX can handle.\n",
					kBuffSize);
		throw(s);

	}

	if(!buff[0])	// end of file
	{	sField.ReleaseBuffer(-1);
		return FALSE;
	}

	// eat white space before the SFM Code (will always be there after a \dis)
	while(*buff && _ismbcspace(*buff))
	{
		*buff='~'; // a hack so that iSpaceLoc, below, isn't set to the space between the "\dis" and marker
		++buff;
	}


	int iSpaceLoc ;
	// figure out where the marker ends and field contents begin
	iSpaceLoc = sField.FindOneOf(" \t\n");
	if(iSpaceLoc <= 1)// [0] should be the slash, [1] at least one char
	{	sField.ReleaseBuffer(-1);
		return FALSE;
	}


	start_buff[iSpaceLoc] = '\0';
	marker = buff + 1; // +1 to skip the slash
	marker.TrimRight();

	contents = start_buff + iSpaceLoc+1;
	contents.TrimLeft();
	contents.TrimRight();

	sField.ReleaseBuffer(-1);
	return TRUE;
}