void NxsBlock::DemandEquals(ProcessedNxsCommand::const_iterator & tokIt, const ProcessedNxsCommand::const_iterator & endIt, const char *contextString) const
	{
	++tokIt;
	if (tokIt == endIt)
		{
		errormsg = "Expecting '=' ";
		if (contextString)
			errormsg.append(contextString);
		errormsg << " but found ; instead";
		--tokIt;
		throw NxsException(errormsg, *tokIt);
		}
	if (!tokIt->Equals("="))
		{
		errormsg = "Expecting '=' ";
		if (contextString)
			errormsg.append(contextString);
		errormsg << " but found " << tokIt->GetToken() << " instead";
		throw NxsException(errormsg, *tokIt);
		}
	}