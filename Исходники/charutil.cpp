/* static */
bool cCharUtil::PeekNextChar(  const TSTRING::const_iterator& cur, 
                               const TSTRING::const_iterator& end, 
                                     TSTRING::const_iterator& first, 
                                     TSTRING::const_iterator& last )
{
    //
    // do we have a valid string here?
    //
    if( cur > end )
    {
        return false;
    }

    if( cur == end )
    {
        first = last = end;
        return false;
    }

    if( *cur == _T('\0') )
    {
        first = last = cur;
        return false;
    }

    first = cur;

    if (!(*cur))
    {
       last = cur;
    }   
    else
    {
#if !IS_AROS
    mblen (NULL, 0);
    int len = mblen(&*cur, MB_CUR_MAX);
    if (len < 0) //invalid multibyte sequence, but let's not blow up.
        len = 1;
    
    last = cur + len;
#else  // AROS mblen() seems broken (as of 6/2016) so don't use it.
    last = cur + 1;
#endif
    }

    return true;
}