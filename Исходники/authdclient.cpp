//	===========================================================================
//	METHOD: authdclient::executecmd
//	===========================================================================
int authdclient::executecmd (const string &command)
{
	string 	result;
	bool   	success 	= false;


	s.puts (command);
	
	// Wait for result
	try
	{
		result = s.gets ();
	}
	catch (exception e)
	{
		syslog (LOG_ERR, "Error talking to authd: %s", e.description);
		result = e.description;
		setlasterror (result);
		return ERR_AUTHD_FAILURE;
	}
	
	// Get Results from string
	success 	= (result && result[0] == '+');
	
	if (! success)
	{
		string rawcmd;
		rawcmd = command;
		rawcmd.cropat (' ');
		
		syslog (LOG_ERR, "Error on command <%s>: %s", rawcmd.str(),
				result.str());
		setlasterror (result);
		
		return ERR_AUTHD_FAILURE;
	}
	
	return ERR_OK;
}