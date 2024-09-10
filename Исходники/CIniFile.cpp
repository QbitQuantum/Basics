TInt CIniData::GetSetting(const TDesC &aValue, TPtrC &aSetting)
/**
Retrieves the value for a particular setting within a block

@param aValue The setting to be retrieved 
@param aSetting On return it contains the value for the setting
@return KErrNone if successful or KErrArgument for fields simply left blank. If the global BlockState is unknown returns KErrNotReady.
*/
	{
	TInt valid(KErrNotReady);	

	if (BlockState != E_UNKNOWN)
	    {
		// first check for CONDITION field
		// if we are NOT looking for this field, we need to trim off any condition
		// field from the block because there may be a setting within it we 
		// want to ignore during our search for this field
        TPtrC pBlock(block);
		TInt tempEnd = blockEnd;
		TPtrC Condition = CONDITION;
		if (aValue.Compare(Condition) != 0)
		    {
			TPtr varCondToken = iToken->Des();
			_LIT(varCondTokenString, "%S=");
			varCondToken.Format(varCondTokenString, &Condition);
			TInt CondPos = pBlock.FindF(varCondToken);
			if (CondPos != KErrNotFound)
				{
				tempEnd = CondPos;
				}
		    }

		// now look for the actual value
        TBool searchAgain = EFalse;
        _LIT(varTokenString, "%S=");
		TPtr varToken = iToken->Des();
		varToken.Format(varTokenString, &aValue);

        TInt pos = KErrNotFound;
        do
            {
            searchAgain = EFalse;
            pos = pBlock.FindF(varToken);
		    if (pos != KErrNotFound && pos < tempEnd)
		        {
                // check that this is a complete match, not a substring
                // match against another similar field, e.g. LoginScript
                // must only match against "LoginScript" not "UseLoginScript"
                if  (pos > 0)
                    {
                    // Previous character must be white space
                    const TChar previousCharacter = pBlock[pos - 1];
                    if  (previousCharacter.IsSpace())
                        {
			            // make sure we haven't overrun our block
			            TInt length = varToken.Length();
			            if (pos + length < tempEnd)
			                {
				            TLex lex(pBlock.Mid(pos + length));

				            // if enclosed by quotes, extract the text within
				            if (lex.Peek() == '"')
				                {
					            lex.SkipAndMark(1);			// start of data

					            // stop at end of quote or line
					            while(lex.Peek() != '"' && lex.Peek() != 10 && lex.Peek() != 13)
									{
						            lex.Inc();
									}
				                }
							else if(lex.Peek() == 10 || lex.Peek() == 13)	// skip empty or blank field value
								{
								return KErrArgument;
								}
							else	// skip any unwanted spaces or tabs in a field value
								{
								TBool fieldValFound=EFalse;
								while(lex.Peek() != 10 && lex.Peek() != 13) 
									{
									if(!fieldValFound)
										{
										while(lex.Peek() == 9 || lex.Peek() == 32) // skip any space or a tab
											{
											lex.SkipAndMark(1);
											}
										if(lex.Peek() == 10 || lex.Peek() == 13) // field value simply filled with space or tab
											{
											return KErrArgument;
											}
										}
									fieldValFound=ETrue;	// start of real data
									lex.Inc();
									}
								}

				            aSetting.Set(lex.MarkedToken().Ptr(),lex.MarkedToken().Length());
							valid = KErrNone;
                            }
                        }
                    else
                        {
                        // E.g. LoginScript matched against UseLoginScript -> must look
                        // for another match after the current one
                        pBlock.Set(pBlock.Mid(pos+1));
                        searchAgain = ETrue;
                        }
                    }
			    }
            }
        while(searchAgain);

	    }

	return valid;
    }