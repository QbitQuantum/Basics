Int32 AbstractVerifier::CountDots(
    /* [in] */ const String& s)
{
    Int32 count = 0;
    for (Int32 i = 0; i < s.GetLength(); i++) {
        if(s.GetChar(i) == '.') {
            count++;
        }
    }
    return count;
}