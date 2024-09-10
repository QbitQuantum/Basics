int unregisterFromGtm(char *line)
{
	char *token;
	int rc;

	for(;GetToken();)
	{
		if (testToken("-n"))
		{
			if (!GetToken())
				return(inputError("No -n option value was found."));
			Free(myname);
			myname = Strdup(token);
			continue;
		}
		else if (testToken("-Z"))
		{
			if (!GetToken())
				return(inputError("No -Z option value was found."));
			if (testToken("gtm"))
			{
				nodetype = GTM_NODE_GTM;
				continue;
			}
			else if (testToken("gtm_proxy"))
			{
				nodetype = GTM_NODE_GTM_PROXY;
				break;
			}
			else if (testToken("gtm_proxy_postmaster"))
			{
				nodetype = GTM_NODE_GTM_PROXY_POSTMASTER;
				break;
			}
			else if (testToken("coordinator"))
			{
				nodetype = GTM_NODE_COORDINATOR;
				break;
			}
			else if (testToken("datanode"))
			{
				nodetype = GTM_NODE_DATANODE;
				break;
			}
			else
			{
				elog(ERROR, "ERROR: Invalid -Z option value, %s\n", token);
				return(-1);
			}
			continue;
		}
		else
			break;
	}
	if (nodetype == 0)
	{
		elog(ERROR, "ERROR: no node type was specified.\n");
		return(-1);
	}

	if (myname == NULL)
		myname = Strdup(DefaultName);
	
	if (!token)
	{
		fprintf(stderr,"%s: No command specified.\n", progname);
		exit(2);
	}
	if (!GetToken())
	{
		elog(ERROR, "ERROR: unregister: no node name was found to unregister.\n");
		return(-1);
	}
	nodename = Strdup(token);
	rc = process_unregister_command(nodetype, nodename);
	Free(nodename);
	return(rc);
}