/*----------------------------------------------------------------------------------------------------------------------
|	Called when the LOG command needs to be parsed from within the GarliReader block.
*/
void GarliReader::HandleLog(
  NxsToken &token)	/* the token used to read from `in' */
	{
	bool starting = false;
	bool stopping = false;
	bool appending = false;
	bool replacing = false;
	bool name_provided = false;
	NxsString logfname;

	// Retrieve all tokens for this command, stopping only in the event
	// of a semicolon or an unrecognized keyword
	//
	for (;;)
		{
		token.GetNextToken();

		if (token.Equals(";"))
			{
			break;
			}
		else if (token.Abbreviation("STOp"))
			{
			stopping = true;
			}
		else if (token.Abbreviation("STArt"))
			{
			starting = true;
			}
		else if (token.Abbreviation("Replace"))
			{
			replacing = true;
			}
		else if (token.Abbreviation("Append"))
			{
			appending = true;
			}
		else if (token.Abbreviation("File"))
			{
			logfname = GetFileName(token);
			name_provided = true;
			}
		else
			{
			errormsg = "Unexpected keyword (";
			errormsg += token.GetToken();
			errormsg += ") encountered reading LOG command";
			throw NxsException(errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
			}
		}

	// Check for incompatible combinations of keywords
	//
	if (stopping && (starting || appending || replacing || name_provided))
		{
		errormsg = "Cannot specify STOP with any of the following START, APPEND, REPLACE, FILE";
		throw NxsException(errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
		}

	if (appending && replacing)
		{
		errormsg = "Cannot specify APPEND and REPLACE at the same time";
		throw NxsException(errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
		}

	if (logf_open && (starting || name_provided || appending || replacing))
		{
		errormsg = "Cannot start log file since log file is already open";
		throw NxsException(errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
		}

	// Is user closing an open log file?
	//
	if (stopping)
		{
		logf.close();
		logf_open = false;

		message = "\nLog file closed";
		PrintMessage();

		return;
		}

	// If this far, must be attempting to open a log file
	//
	if (!name_provided)
		{
		errormsg = "Must provide a file name when opening a log file\n";
		errormsg += "e.g., log file=doofus.txt start replace;";
		throw NxsException(errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
		}   

	if (appending)
		{
		logf_open = true;
		logf.open(logfname.c_str(), ios::out | ios::app);

		message = "\nAppending to log file ";
		message += logfname;
		PrintMessage();
		}

	else if (replacing)
		{
		logf_open = true;
		logf.open(logfname.c_str());

		message = "\nReplacing log file ";
		message += logfname;
		PrintMessage();
		}

	else 
		{
		bool exists = FileExists(logfname.c_str());
		bool userok = true;
		if (exists && !UserQuery("Ok to replace?", "Log file specified already exists", GarliReader::UserQueryEnum(GarliReader::uq_yes | GarliReader::uq_no)))
			userok = false;

		if (userok)
			{
			logf_open = true;
			logf.open(logfname.c_str());
			}

		if (exists && userok)
			{
			message = "\nReplacing log file ";
			message += logfname;
			}

		else if (userok)
			{
			message = "\nLog file ";
			message += logfname;
			message += " opened";
			}

		else
			{
			message = "\nLog command aborted";
			}

		PrintMessage();
		}
	}