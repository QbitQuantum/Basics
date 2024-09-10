void NxsSetReader::ReadSetDefinition(
  NxsToken &token, 
  const NxsLabelToIndicesMapper & mapper, 
  const char * setType, /* "TAXON" or "CHARACTER" -- for error messages only */ 
  const char * cmdName, /* command name -- "TAXSET" or "EXSET"-- for error messages only */ 
  NxsUnsignedSet * destination, /** to be filled */
  const NxsUnsignedSet * taboo)
	{
	NxsString errormsg;
	NxsUnsignedSet tmpset;
	NxsUnsignedSet dummy;
	if (destination == NULL)
		destination = & dummy;
	unsigned previousInd = UINT_MAX;
	std::vector<unsigned> intersectVec;
	while (!token.Equals(";"))
		{
		if (taboo && token.Equals(","))
			return;
		if (token.Equals("-"))
			{
			if (previousInd == UINT_MAX)
				{
				errormsg = "The '-' must be preceded by number or a ";
				errormsg << setType << " label in the " << cmdName << " command.";
				throw NxsException(errormsg, token);
				}
			token.GetNextToken();
			if (token.Equals(";") || token.Equals("\\"))
				{
				errormsg = "Range in the ";
				errormsg << setType << " set definition in the " << cmdName << " command must be closed with a number or label.";
				throw NxsException(errormsg, token);
				}
			unsigned endpoint;
			if (token.Equals("."))
				endpoint = mapper.GetMaxIndex();
			else
				{
				tmpset.clear();
				unsigned nAdded = NxsSetReader::InterpretTokenAsIndices(token, mapper, setType, cmdName, &tmpset);
				if (nAdded != 1)
					{
					errormsg = "End of a range in a ";
					errormsg << setType << " set definition in the " << cmdName << " command must be closed with a single number or label (not a set).";
					throw NxsException(errormsg, token);
					}
				endpoint = *(tmpset.begin());
				if (endpoint < previousInd)
					{
					errormsg = "End of a range in a ";
					errormsg << setType << " set definition in the " << cmdName << " command must be a larger index than the start of the range (found ";
					errormsg << previousInd + 1 << " - " << token.GetToken();
					throw NxsException(errormsg, token);
					}
				}
			token.GetNextToken();
			if (token.Equals("\\"))
				{
				token.GetNextToken();
				NxsString t = token.GetToken(); 
				unsigned stride = 0;
				try
					{
					stride = t.ConvertToUnsigned();
					}
				catch (const NxsString::NxsX_NotANumber &)
					{}
				if (stride == 0)
					{
					errormsg = "Expecting a positive number indicating the 'stride' after the \\ in the ";
					errormsg << setType << " set definition in the " << cmdName << " command. Encountered ";
					errormsg << t;
					throw NxsException(errormsg, token);
					}
				AddRangeToSet(previousInd, endpoint, stride, destination, taboo, token);
				token.GetNextToken();
				}
			else
				AddRangeToSet(previousInd, endpoint, 1, destination, taboo, token);
			previousInd = UINT_MAX;
			}
		else 
			{
			tmpset.clear();
			const unsigned nAdded = NxsSetReader::InterpretTokenAsIndices(token, mapper, setType, cmdName, &tmpset);
			if (taboo != NULL)
				{
				set_intersection(taboo->begin(), taboo->end(), tmpset.begin(), tmpset.end(), back_inserter(intersectVec));
				if (!intersectVec.empty())
					{
					errormsg << "Illegal repitition of an index (" << 1 + *(intersectVec.begin()) << ") in multiple subsets.";
					throw NxsException(errormsg, token);
					}
				}
			if (nAdded == 1 )
				{
				previousInd = *(tmpset.begin());
				destination->insert(previousInd);
				}
			else
				{
				previousInd = UINT_MAX;
				destination->insert(tmpset.begin(), tmpset.end());
				}
			token.GetNextToken();
			}
		}
	}