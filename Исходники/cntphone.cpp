/**
 * Extracts the real phone number from a contacts phone number field.
 * This method strips away any DTMF strings or extended services. An empty
 * descriptor is returned in aRawNumber if the field doesn't have a valid phone
 * number.
 *
 * @param aTextualNumber Descriptor containing a contacts model phone number field
 * @param aRawNumber Descriptor to write the raw number to (loaned by caller)
 */
void CContactDefaultPhoneNumberParser::ExtractRawNumber(const TDesC& aTextualNumber, TDes& aRawNumber)
{
    aRawNumber.Zero();

    TInt length = aTextualNumber.Length();
    if (length==0)
    {
        return;
    }


    TPtrC numberPtr( aTextualNumber );
    TUint firstChar = numberPtr[0];

    //gobble spaces
    while (TChar(firstChar).IsSpace())
    {
        --length;
        if (length==0)
        {
            return;
        }

        numberPtr.Set(numberPtr.Right(length));
        firstChar = numberPtr[0];
    }

    // Get left hand side
    if ( firstChar == KSymbolAsterisk || firstChar == KSymbolHash )
    {
        //Check if there is plus on first five chars:
        TInt newStartPlace = numberPtr.Locate( KSymbolPlus );
        if ( newStartPlace>=KPlusWithinChars || newStartPlace==KErrNotFound )
        {
            // There is always star or hash...
            newStartPlace = Max( numberPtr.LocateReverse(KSymbolAsterisk ) ,numberPtr.LocateReverse( KSymbolHash) );
        }

        length = length - newStartPlace -1;
        if ( length <= 0 )
        {
            return;
        }
        numberPtr.Set( numberPtr.Right( length ) );
        firstChar = numberPtr[0];
    }

    //test condition to satisfy the removal of '(' the next if
    //statement removes the '+' if needed
    if ( firstChar == KSymbolOpenBrace )
    {
        length--;
        numberPtr.Set( numberPtr.Right( length ) );
        // This may be the only character in the descriptor so only access if
        // 1 or more characters left.
        if (length > 0 )
        {
            firstChar = numberPtr[0];
        }
    }

    if ( firstChar == KSymbolPlus )
    {
        length--;
        numberPtr.Set( numberPtr.Right( length ) );
    }

    if (length==0)
    {
        return;
    }

    // Find right hand side
    TLex numberLexer( numberPtr );
    for ( ; ; )
    {
        TChar nextChar = numberLexer.Peek();
        if ( !nextChar )
        {
            break;
        }

        if ( nextChar.IsDigit() )
        {
            aRawNumber.Append( nextChar );
            numberLexer.Inc();
        }
        else if ( nextChar == KSymbolAsterisk || nextChar == KSymbolHash )
        {
            aRawNumber.Zero();
            return;
        }
        else
        {
            nextChar.LowerCase();
            if ( nextChar == KSymbolPause
                    || nextChar == KSymbolWait
                    || nextChar == KSymbolPlus)
            {
                break;
            }
            numberLexer.Inc();
        }
    }
}