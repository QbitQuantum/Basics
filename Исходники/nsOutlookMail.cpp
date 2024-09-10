void nsOutlookMail::SplitString( nsString& val1, nsString& val2)
{
    nsString  temp;

    // Find the last line if there is more than one!
    PRInt32 idx = val1.RFind( "\x0D\x0A");
    PRInt32  cnt = 2;
    if (idx == -1) {
        cnt = 1;
        idx = val1.RFindChar( 13);
    }
    if (idx == -1)
        idx= val1.RFindChar( 10);
    if (idx != -1) {
        val1.Right( val2, val1.Length() - idx - cnt);
        val1.Left( temp, idx);
        val1 = temp;
        SanitizeValue( val1);
    }
}