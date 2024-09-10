DWORD
DWordXorLrl( char *szSym )

/*++

Routine Description:

    This function will take an ascii character string and generate
    a hash for that string.  The hash algorithm is the CV NB08 hash
    algorithm.


Arguments:

    szSym    - a character pointer, the first char is the string length


Return Value:

    The generated hash value.

--*/

{
    char                *pName = szSym+1;
    int                 cb =  *szSym;
    char                *pch;
    char                c;
    DWORD               hash = 0;
    DWORD UNALIGNED     *pul = (DWORD *) pName;
    static              rgMask[] = {0, 0xff, 0xffff, 0xffffff};

    //
    // We replace all "::" to "__"
    //
    c = *(pName+cb);
    *(pName+cb) = '\0';
    pch = strstr( pName, "::" );
    if ( pch ) {
        *pch++ = '_';
        *pch   = '_';
    }
    *(pName+cb) = c;

    pch = pName + cb - 1;
    while (isdigit(*pch)) {
        pch--;
    }

    if (*pch == '@') {
        cb = pch - pName;
    }

    for (; cb > 3; cb-=4, pul++) {
        hash = _lrotl(hash, 4);
        hash ^= (*pul & 0xdfdfdfdf);
    }

    if (cb > 0) {
        hash = _lrotl(hash,4);
        hash ^= ((*pul & rgMask[cb]) & 0xdfdfdfdf);
    }

    return hash;
}                               /* DWordXorLrl() */