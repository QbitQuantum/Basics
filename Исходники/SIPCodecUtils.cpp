// -----------------------------------------------------------------------------
// SIPCodecUtils::ValueWithoutQuotes
// -----------------------------------------------------------------------------
//
TInt SIPCodecUtils::ValueWithoutQuotes(
    const TDesC8& aValue,
    TPtrC8& aWithoutQuotes)
    {
    if (aValue.Length() > 0)
        {
        TLex8 lex(aValue);
        lex.SkipSpace();
        if (lex.Get() == '"')
            {
            // Remove first quote
            TPtrC8 remainder(aValue.Mid(1));
            // Ensure that ending quote exists.
            if(remainder.LocateReverse('"') != (remainder.Length()-1))
                {
                return KErrArgument;
                }
	        aWithoutQuotes.Set(remainder.Left(remainder.Length()-1));
            }
        else
            {
            return KErrArgument;
            }
        }
    return KErrNone;
    }