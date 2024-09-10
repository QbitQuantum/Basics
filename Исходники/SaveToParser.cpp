//////////
//
// Searches through the haystack to find the needle.  Needle is NULL-
// terminated, and haystack is length-terminated.
//
//////
bool iIsNeedleInHaystack(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength)
{
    s32 lnI;

    // Check to see if the specified word / phrase / whatever exists on this line
    for (lnI = 0; lnI <= haystackLength - needleLength; lnI++)
    {
        if (_memicmp(haystack + lnI, needle, needleLength) == 0)
            return(true);
    }

    // Failure
    return(false);
}