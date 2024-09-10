//
// Remove szOlds from the end of the string.
//
SString SString::TrimEnd ( const char* szOld ) const
{
    const size_t uiOldLength = strlen ( szOld );
    SString strResult = *this;
    while ( strResult.length () >= uiOldLength && strResult.substr ( strResult.length () - uiOldLength ) == szOld )
        strResult = strResult.substr ( 0, strResult.length () - uiOldLength );
    return strResult;
}