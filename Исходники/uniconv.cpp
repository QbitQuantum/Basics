// This takes a name and does a lookup into the ccsid table (from ccsid.h)
// to find the corresponding ccsid. It also checks if the string ends in s390
// and returns that information to the caller.
// The lookup into the table is done via a binary search since we know that the
// table was nicely sorted for us.
static int getccsid(const char *s,int * is390)
{
    char tmpstr[_AE_MAX_CODESET_NAME_LENGTH];
    int start;
    int limit;
    int index;
    int result;
    int thelen;

    // Clean up the name....
    if (s == NULL)
        return -1;
    if ((thelen = stripNameCopy(s,tmpstr,_AE_MAX_CODESET_NAME_LENGTH-1)) == -1)
        return -1;

    // Check for the S390 string in the name
    *is390 = 0;
    if ( (strstr((char *)tmpstr, "S390")) != NULL )
        *is390 = 1;

    // Now lookup the name via a binary search
    start = 0;
    limit = _AE_NUM_OF_CODESETS;
    index = limit/2;
    while ( ((result=strcoll(tmpstr, CCSID_MAPPING[index].NAME)) != 0) &&
            (start < limit-1) ) {
        if (result < 0)
            limit = index;
        else
            start = index;
        index = (start+limit)/2;
    }

    if (result != 0 && start >= limit-1)
        return -1;

    return CCSID_MAPPING[index].CCSID;
}