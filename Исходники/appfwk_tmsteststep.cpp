TInt CTmsTestStep::ReadNextLineL( RFile &aFile, TDes8 &aLine )
// read a cr/lf limiited line from the file,  assumes file is a valid file
// and that aLine is of sufficient length to hold the data
{
    aLine.Zero();
    TBuf8<1> chr;
    for (;;)
    {
        aFile.Read(chr);
        if ( chr.Length() == 0 )
        {
            break;
        }
        if (chr.CompareF(KRet) == 0)
        {
            // got a line, exctract newline as well
            aFile.Read(chr);
            break;
        }
        else
        {
            aLine.Append(chr);
        }
    }

    return aLine.Length();
}