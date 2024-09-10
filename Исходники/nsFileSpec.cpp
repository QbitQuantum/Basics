//----------------------------------------------------------------------------------------
nsFileURL::nsFileURL(const nsString& inString, PRBool inCreateDirs)
//----------------------------------------------------------------------------------------
{
    NS_LossyConvertUCS2toASCII cstring(inString);
    if (!inString.Length())
        return;
    NS_ASSERTION(strstr(cstring.get(), kFileURLPrefix) == cstring.get(),
                 "Not a URL!");
    // Make canonical and absolute. Since it's a parameter to this constructor,
    // inString is escaped. We want to make an nsFilePath, which requires
    // an unescaped string.
    nsSimpleCharString unescapedPath(cstring.get() + kFileURLPrefixLength);
    unescapedPath.Unescape();
    nsFilePath path(unescapedPath, inCreateDirs);
    *this = path;
} // nsFileURL::nsFileURL