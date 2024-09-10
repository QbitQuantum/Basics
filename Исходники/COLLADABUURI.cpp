// This function will take a resolved URI and create a version of it that is relative to
// another existing URI.  The new URI is stored in the "originalURI"
bool URI::makeRelativeTo ( const URI& relativeToURI, bool ignoreCase)
{
    // Can only do this function if both URIs have the same scheme and authority
    if (mScheme != relativeToURI.mScheme  ||  mAuthority != relativeToURI.mAuthority)
        return false;

    // advance till we find a segment that doesn't match
    WideString thisPathWideSring = StringUtils::utf8String2WideString(getPath());
    WideString relativeToPathWideSring = StringUtils::utf8String2WideString(relativeToURI.getPath());
    const wchar_t *this_path        = thisPathWideSring.c_str();
    const wchar_t *relativeTo_path  = relativeToPathWideSring.c_str();
    const wchar_t *this_slash       = this_path;
    const wchar_t *relativeTo_slash = relativeTo_path;
    /*		const char *this_path        = getPath().c_str();
    		const char *relativeTo_path  = relativeToURI.getPath().c_str();
    		const char *this_slash       = this_path;
    		const char *relativeTo_slash = relativeTo_path;
    */
    while( *this_path )
    {

        if  ( ignoreCase )
        {
            wchar_t characters[3];
            characters[0] = *this_path;
            characters[1] = *relativeTo_path;
            characters[2] = 0;

            boost::to_lower(characters);

            if  ( characters[0] != characters[1] )
                break;
        }
        else
        {
            if (*this_path != *relativeTo_path)
                break;
        }

        if(*this_path == '/')
        {
            this_slash = this_path;
            relativeTo_slash = relativeTo_path;
        }
        this_path++;
        relativeTo_path++;
    }

    // Decide how many ../ segments are needed (Filepath should always end in a /)
    int segment_count = 0;
    relativeTo_slash++;
    while(*relativeTo_slash != 0)
    {
        if(*relativeTo_slash == '/')
            segment_count ++;
        relativeTo_slash++;
    }
    this_slash++;

    String newPath;
    if ( segment_count == 0 )
    {
        newPath = "./";
    }
    else
    {
        for (int i = 0; i < segment_count; i++)
            newPath += "../";
    }
    WideString thisSlashWideString(this_slash);
    newPath += StringUtils::wideString2utf8String(thisSlashWideString);

    set("", "", newPath, mQuery, mFragment, 0/*relativeToURI*/);
    return true;
}