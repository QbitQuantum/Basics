/**
Search algorithm for searching phone numbers

@param aText Text that will be parsed
@return ETrue if any Phone Number items were found else returns EFalse
@leave KErrNone, if successful; otherwise one of the other system-wide error codes.
@panic ETulPanicDescriptorLength in debug build if item's position 
and/or length is out of the document's range.
*/
TBool CTulAddressStringTokenizer::SearchPhoneNumberL( const TDesC& aText )
    {
    TLexMark startMark; // Points to the start of the found phone number
    TLexMark endMark; // Points to the end of the found phone number
    TLexMark mark;
    const TInt end = aText.Length();

    TLex number = aText;

    while ( !(number.Eos()) )
        {
        TInt numberCount = 0; // How many real numbers (1234567890)
        TInt bracketsOpen = 0; // How many brackets are currently open
        TInt brackets = 0; // How many brackets overall

        TChar charac = number.Peek();

        while( (!(IsValidPhoneNumberChar( charac ) || charac == '+'
               || charac == '(' ) || charac == '-' || charac == '.' || charac == '/') 
			   && !(number.Eos()) && number.Offset() < end )
            {
            number.Inc();
            charac = number.Peek();
            }

        if ( number.Offset() >= end )
            break;
        
        if ( number.Peek() == '#' )
			{
			number.Inc();
			if (number.Peek() == '.' )
				continue;

			number.UnGet();
			}

        if ( number.Peek() == '+' )
            { // '+' has to be followed by a number (not # or * ...)
            number.Inc();
            if ( !(number.Peek().IsDigit()) )
                continue;

            number.UnGet();
            }

        if ( number.Peek() == '(' )
            { // '(' has to be followed by valid phone number 
              // character (whitespaces are allowed before) or '+' is a next character
            number.Inc();
            if ( !(number.Peek() == '+') )
                {
                number.Mark(mark);
                number.SkipSpace();
                charac = number.Peek();
                if ( !( IsValidPhoneNumberChar(charac) || charac == '+' 
                    || charac == '(' ) || charac == '-' || charac == '.' || charac == '/')
                    {
                    number.Inc();
                    continue;
                    }
                else
                    {
                    number.UnGetToMark(mark);
                    number.UnGet();
                    number.Mark(startMark);
                    }
                } 
            else
                {
                number.UnGet();
                number.Mark(startMark);
                number.Inc();
                }

            bracketsOpen++;
            brackets++;
            }
        else
            number.Mark(startMark);

        if ( number.Peek().IsDigit() )	// If the character was a number
            numberCount++;
        else if ( bracketsOpen > 0 ) 
            { 
            number.Inc();
            TChar next  = number.Peek();
            TInt bracketsOpen2 = bracketsOpen;
            while( (IsValidPhoneNumberChar( next ) || next.IsSpace()
                || next == '(' || next == ')' || next == 'p' || next == '+'
                || next == 'w' ) && !(number.Eos()) && number.Offset() < end)
                {
                if ( next == '(' )
                    bracketsOpen2++;
                else if ( next == ')' )
                    bracketsOpen2--;
                
                if ( bracketsOpen2 == 0 )
                    break;

                number.Inc();
                next = number.Peek();
                }

            number.UnGetToMark(startMark);
            if ( bracketsOpen2 != 0 )
                {
                number.Inc();
                continue;
                }
            }

        number.Inc();
        while ( number.Peek() == '(' && !(number.Eos()) && bracketsOpen > 0 )
            {
            number.Inc();
            bracketsOpen++;
            }

        if ( number.Peek() == '+' && bracketsOpen > 0 )
            number.Inc();

        // a Valid first character has been found. Let's go forward as long as valid characters are found.
        charac = number.Peek();

        while( (IsValidPhoneNumberChar( charac ) || charac.IsSpace()
            || charac == '(' || charac == ')' || charac == 'p'
            || charac == 'w' ) && !(number.Eos()) && number.Offset() < end
            && charac != KCharLinefeed && charac != KCharFormfeed 
            && charac != KCharCarriageReturn
            && charac != KCharLineSeparator
            && charac != KCharParagraphSeparator )
            {
            if ( number.Peek() == '(' )
                { // '(' can't be the last character in phone number
                number.Mark(mark);
                number.Inc();
                
                TChar spaceJump = number.Peek();
                while ( !number.Eos() && spaceJump.IsSpace() && spaceJump != KCharLinefeed 
                        && spaceJump != KCharFormfeed && spaceJump != KCharCarriageReturn 
                        && charac != KCharLineSeparator && spaceJump != KCharParagraphSeparator)
                    {
                    number.Inc();
                    spaceJump = number.Peek();
                    }
                
                if ( !(IsValidPhoneNumberChar(number.Peek())) && number.Peek() != ')'
                     && number.Peek() != '(' )
                    {
                    number.UnGetToMark(mark);
                    break;
                    }

                TChar next  = number.Peek();
                TInt bracketsOpen2 = bracketsOpen + 1;
                while( (IsValidPhoneNumberChar( next ) || next.IsSpace()
                    || next == '(' || next == ')' || next == 'p'
                    || next == 'w' ) && !(number.Eos()) && number.Offset() < end)
                    {
                    if ( next == '(' )
                        bracketsOpen2++;
                    else if ( next == ')' )
                        bracketsOpen2--;

                    if ( bracketsOpen2 == 0 )
                        break;

                    number.Inc();
                    next = number.Peek();
                    }

                number.UnGetToMark(mark);

                if ( bracketsOpen2 != 0 )
                    break;

                bracketsOpen++;
                brackets++;
                }
            else if ( number.Peek() == ')' )
                {
                if ( bracketsOpen <= 0 )	// there has to be equal number of brackets
                    break;

                bracketsOpen--;
				number.Mark(mark);
                number.Inc();
				if ( number.Peek() == '.' )	// '.' is not allowed after ')'
                    break;

                number.UnGetToMark(mark);
                }
            else if ( number.Peek() == '-' || number.Peek() == 'w' 
                        || number.Peek() == 'p' || number.Peek() == '.' || number.Peek() == '/')
                { // Hyphen mark and 'p' & 'w' chars must be followed by a number
				TChar last = number.Peek();
                number.Mark(mark);
                number.Inc();
                
                TChar spaceJump = number.Peek();
                while ( !number.Eos() && spaceJump.IsSpace() && spaceJump != KCharLinefeed 
                        && spaceJump != KCharFormfeed && spaceJump != KCharCarriageReturn 
                        && charac != KCharLineSeparator && spaceJump != KCharParagraphSeparator )
                    {
                    number.Inc();
                    spaceJump = number.Peek();
                    }
                    
                if ( !(number.Peek().IsDigit()) )
                    {
					if (last == '.' && number.Peek() == ')' && bracketsOpen > 0 )
						continue;
					else
						{
						number.UnGetToMark(mark);
						break;
						}
                    }

                number.UnGetToMark(mark);
                }
            else if ( number.Peek().IsDigit() )
                numberCount++;

            number.Inc();
            charac = number.Peek();
            }

        // Get rid of whitespaces from the end
        number.UnGet();
        while( number.Peek().IsSpace() && !(number.Eos()))
            number.UnGet();

        number.Inc();
        // ------------------------------------
        number.Mark(endMark);

        // If they exist, remove brackets from the beginning and the end
        number.Mark(mark); // Let's mark where to continue the search
        TBool endBrackets = ETrue;
        do
            {
            number.UnGet();

            if ( number.Peek() == ')' )
                {
                number.UnGetToMark(startMark);
                if ( number.Peek() == '(' )
                    {
                    // If there's more than one pair of brackets -> don't strip them.
                    if ( brackets > 1 )
                        break;

                    number.Inc();
                    number.Mark(startMark);
                    number.UnGetToMark(endMark);
                    number.UnGet();
                    number.Mark(endMark);
                    // Get rid of whitespaces and periods from the end and from the beginning
					number.UnGet();
                    while ( (number.Peek().IsSpace() || number.Peek() == '.') 
                            && number.Offset() > number.MarkedOffset(startMark) )     
                        { // from the end
                        number.UnGet();
                        }
					number.Inc();
                    number.Mark(endMark);
                    number.UnGetToMark(startMark);
                    while ( (number.Peek().IsSpace() || number.Peek() == '.') 
                            && number.Offset() < number.MarkedOffset(endMark) )     
                        { // from the beginning
                        number.Inc();
                        }
                    number.Mark(startMark);
                    number.UnGetToMark(endMark);
                    // ----
                    }
                else
                    endBrackets = EFalse;
                }
            else
                endBrackets = EFalse;
            }
        while ( endBrackets );

        number.UnGetToMark(mark);
        // ----------------        

        if ( numberCount <= KFindItemMaxNumbers && numberCount >= iMinNumbers )
            {
			TPtrC tokenPtr = number.MarkedToken(startMark);
			TInt tokensEnd = tokenPtr.Length();
			TInt numbers = 0;
			TInt partialNumber = 0;
			TBool wasValidPhoneNumber = ETrue;
			TInt i = 0;

			for ( ; i < tokensEnd; i++ )
				{
				if ( tokenPtr[i] == '.' )
					partialNumber = 0;
				else if ( ((TChar)tokenPtr[i]).IsDigit() )
					{
					numbers++;
					partialNumber++;
					}

				if ( ( partialNumber == 1 || partialNumber == 2 ) && i + 1 < tokensEnd )
					{
					if ( tokenPtr[i + 1] == '.' )
						wasValidPhoneNumber = EFalse;
					}
				}
				
			if (!wasValidPhoneNumber && numbers > 6)
				wasValidPhoneNumber = ETrue;
			
			if (wasValidPhoneNumber)
				{
	            __ASSERT_DEBUG( number.MarkedOffset(startMark) + number.MarkedOffset(endMark) 
	                            - number.MarkedOffset(startMark) <= aText.Length(), 
	                            Panic(ETulPanicDescriptorLength) );

	            AddItemL( number.MarkedOffset(startMark), 
	                      number.MarkedOffset(endMark) - number.MarkedOffset(startMark), 
	                      EFindItemSearchPhoneNumberBin );
				}
			}

        }

    return (iFoundItems->Count() > 0);
    }