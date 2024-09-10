void
GMMIMEParser::ParseMIMEHeader
	(
	std::istream&		input,
	GMIMEHeader*	header,
	const JBoolean	display
	)
{
	JString data;
	JCharacter c	= input.peek();
	if (c == '\n')
		{
//		input.get(c);
		}
//	input >> std::ws;

	// first we need to search for the first empty line. This line is the
	// end of the header.

	JString line;
	while (1)
		{
		JBoolean found;
		line = JReadLine(input, &found);
		if (line.IsEmpty())
			{
			break;
			}
		if (isspace(line.GetFirstCharacter()))
			{
			line.TrimWhitespace();
			if (line.IsEmpty())
				{
				break;
				}
			data.AppendCharacter(' ');
			}
		else if (!data.IsEmpty())
			{
			data.AppendCharacter('\n');
			}
		data += line;
		}
	data.AppendCharacter('\n');

	// we now need to search through the header for parameter:value pairs
	// using the gmime_header_regex defined above.

	JArray<JIndexRange> ranges;
	gmime_header_regex.MatchAll(data, &ranges);

	JSize count = ranges.GetElementCount();
	for (JSize i = 1; i <= count; i++)
		{
		JIndexRange range = ranges.GetElement(i);
		JString parmValPair = data.GetSubstring(range);
		JString parm;
		JString val;
		if (parmValPair.BeginsWith("MIME") ||
			parmValPair.BeginsWith("Mime") ||
			parmValPair.BeginsWith("Content"))
			{
			CleanParmValPair(parmValPair, &parm, &val);
			parm.ToLower();
			if (parm == "mime-Version")
				{
				val.TrimWhitespace();
				header->SetVersion(val);
				}
			else if (parm == "content-type")
				{
				ParseContentType(val, header);
				}
			else if (parm == "content-transfer-encoding")
				{
				val.TrimWhitespace();
				val.ToLower();
				header->SetEncoding(val);
				}
			else if (parm == "content-disposition")
				{
				ParseContentDisposition(val, header);
				}
			}
		}

	// this is a nested message, so some of the headers need to be displayed
	if (display)
		{
		JString text = "---------\n";
		JIndex findex	= 1;
		if (data.BeginsWith("From: ") || data.LocateSubstring("\nFrom: ", &findex))
			{
			if (findex > 1)
				{
				findex ++;
				}
			JIndex eindex	= findex;
			if (data.LocateNextSubstring("\n", &eindex) && (eindex > findex + 1))
				{
				text += data.GetSubstring(findex, eindex - 1);
				text += "\n";
				}
			}
		findex	= 1;
		if (data.BeginsWith("Date: ") || data.LocateSubstring("\nDate: ", &findex))
			{
			if (findex > 1)
				{
				findex ++;
				}
			JIndex eindex	= findex;
			if (data.LocateNextSubstring("\n", &eindex) && (eindex > findex + 1))
				{
				text += data.GetSubstring(findex, eindex - 1);
				text += "\n";
				}
			}
		findex	= 1;
		const JCharacter* kSubjectStr	= "Subject: ";
		if (data.BeginsWith("Subject: ") || data.LocateSubstring("\nSubject: ", &findex))
			{
			if (findex > 1)
				{
				findex ++;
				}
			JIndex eindex	= findex;
			if (data.LocateNextSubstring("\n", &eindex) && (eindex > findex + 1))
				{
				text += data.GetSubstring(findex, eindex - 1);
				text += "\n";
				}
			}
		WriteTextString(&text, GMIMEHeader());
		}
}