/**
Checks whether this is a STATUS response.
If it is, then it starts buiding an atom tree.  
If the tree is completed then the data is parsed straight away.  Otherwise, more data is requested.
If the atom tree is completed by this line, then tree is parsed to decode the response.
@return ENotRecognised if this is not a STATUS response
		EResponseIncomplete if this is a STATUS resposne, but more data is required.
		ECompleteUntagged if this is a STATUS response that has been fully parsed.
*/
CImapCommand::TParseBlockResult CImapStatus::ParseUntaggedResponseL()
	{
	TParseBlockResult result = ENotRecognised;
	
	TPtrC8 response = GetNextPart();
	if(response.CompareF(KImapTxtStatus) == 0)
		{
		TPtrC8 remainingData = Remainder();
   		TBool wantMoreData = iAtomParser->ProcessLineL(remainingData);
   		if (wantMoreData)
   			{
   			result = EResponseIncomplete;
   			}
   		else
   			{
   			ParseStatusResponseL();
   			result = ECompleteUntagged;
   			}
		}
	
	return result;
	}