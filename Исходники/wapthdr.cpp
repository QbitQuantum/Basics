/**
 *  Parses a string of hex characters representing a number
 *  
 *  @param aInValue descriptor containing the number
 *  @param aBigEndian true if number is big endian
 *  @param aRadix Radixbase; 16, 10 etc
 *  @return TInt the parsed number
 *  @leave Panics with KPanicInvalidParseNumber error code, if not a
 *  number. Maximum width of the hex value can be 4.
 *  
 *  TODO use TLex instead
 */
TInt TWapTextMessage::ParseNumber(const TDesC8& aInValue,
                                  TBool   aBigEndian,
                                  TInt    aRadix)
    {
    OstTraceDefExt1(OST_TRACE_CATEGORY_DEBUG, TRACE_INTERNALS, TWAPTEXTMESSAGE_PARSENUMBER_1, "TWapTextMessage::ParseNumber [%s]", aInValue);
    // least significant byte first
    TInt Values[4] = {0,0,0,0};
    TInt Temp = 0;
    TInt length = aInValue.Length();
    TInt i = 0;
    TInt Value = 0;

    __ASSERT_DEBUG(length<5,Panic(KPanicInvalidParseNumber));
    if( length >= 5 )
        return KErrNotFound;
    for(i=0; i<length; i++)
        {
        Temp = aInValue[i];
        if (Temp>='0' && Temp<='9')
            Temp-='0';
        else if (Temp>='A' && Temp<='Z')
            Temp = Temp - 'A'+10;
        else if (Temp>='a' && Temp<='z')
            Temp = Temp - 'a'+10;
        else
            return KErrNotFound;
        if (aBigEndian)
            Values[(length-1)-i]=Temp;
        else
            Values[i]=Temp;
        }

    // build the value
    Value=Values[0];
    TInt Base=1;
    for(i=1; i<length; i++)
        {
        Base*=aRadix;
        Value+=(Base)*Values[i];
        }

    return Value;
    } // TWapTextMessage::ParseNumber