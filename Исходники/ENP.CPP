//
//  ParseMessageL()
//
//  Simple Notification:
//      Looks for number of messages and "From:" field
//      writes numMsg into the parsed field array, sets
//      entry.iDetails to the "From:" 
//  Complicated Notification:
//      does the above and writes everything else into
//      the array....
//
void CEmailNotificationParser::ParseMessageL()
    {
    TBool isSimpleNotification = EFalse; 
    TLex  tokenLex;
    TPtrC fieldName;
    TPtrC fieldValue;

	// reset parsedfield array
	for(TInt i = iParsedFieldArray->Count();--i>=0;)
		(*iParsedFieldArray)[i]->SetFieldValueL(_L(""));

    // Set extraction mark at first character
    iSms.SkipSpaceAndMark();
	if(iSms.Peek() == KCharSlash)
		{
		// Check first line is <header>
		iSms.SkipCharacters();

		if (iSms.MarkedToken() != KEmailHeader)
			{
			User::Leave(KBspInvalidMessage);
			}
		// Get <new-amount> from second line and check for terminating linefeed
		iSms.SkipSpaceAndMark();
		}

    // Val() seeks forward from next char position, looking for valid
    // digits and incrementing next char as it goes.
    if (!(iSms.Val(iMessageCount) == KErrNone  &&  iMessageCount >= 0))     // If marked token is not a valid positive integer
        {
        iMessageCount = 0;
        User::Leave(KBspInvalidMessage);
        }
    else
        {
        fieldValue.Set(iSms.MarkedToken());                            //  The message count..
        AddParsedFieldL(KHeaderNumberMessages, fieldValue, ETrue);
        }

    // Next character may now be at newline or space after integer.
    // If at space, advance to newline.
    while (iSms.Peek() != KCharLineFeed && !iSms.Eos())
        iSms.Inc();

    iSms.SkipSpaceAndMark();

    // Now parse the rest of the fields, if any.
    while (!iSms.Eos())
        {
        while (iSms.Peek() != KCharLineFeed  &&  !iSms.Eos())
            iSms.Inc();     //  Skip to next delimiter

        if (iSms.Eos())
            break;          //  we've finished break out of the function

        if (iSms.TokenLength() == 0)
            User::Leave(KBspSmartMessageInvalidToken);

        //  Parsing....
        tokenLex.Assign(iSms.MarkedToken());        // Assign token to a new TLex
        while (tokenLex.Peek() != KCharColon  &&  !tokenLex.Eos())
            tokenLex.Inc();     //  Advance to a ':'

        if (tokenLex.Eos()  ||  tokenLex.TokenLength() == 0)
            User::Leave(KBspSmartMessageInvalidToken);


        fieldName.Set(tokenLex.MarkedToken());      // Store (pointer to) field name
        tokenLex.Inc();

		//fix for DEF017686
		LeaveIfEmptyFieldsL(fieldName,tokenLex);
		
        
        tokenLex.SkipSpaceAndMark();                // Step past optional spaces

		//fix for DEF017686
        LeaveIfEmptyFieldsL(fieldName,tokenLex);
	
		// if it's the server id field try to extract the id value
		// and match to an existing email service
		if(fieldName.CompareF(KHeaderServerId)==KErrNone)
			{
			TInt valErr = tokenLex.Val(iServerId);
			if(valErr != KErrNone)
				iServerId = 0;
			else
				GetEmailServicesL();

			tokenLex.UnGetToMark();
			}	
		fieldValue.Set(tokenLex.Remainder());       // Store (pointer to) field value

        if(!isSimpleNotification)
            {
            AddParsedFieldL(fieldName, fieldValue, EFalse);
            }		

        // Successfully parsed a token. Move iSms's next character past the
        // (linefeed) delimiter, set the extraction mark and reiterate to
        // look for next token.
        iSms.SkipSpaceAndMark();
        }
    }