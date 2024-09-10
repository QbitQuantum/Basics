static int EnterDict( unsigned char *bucketsP, unsigned short ndicpages, unsigned char *entry, unsigned entrylen )
{
    unsigned short      uStartIndex;
    unsigned short      uStep;
    unsigned short      uStartPage;
    unsigned short      uPageStep;
    unsigned short      uIndex;
    unsigned short      uPage;
    unsigned short      n;
    unsigned            u;
    unsigned            nbytes;
    unsigned char       *aP;
    unsigned char       *zP;

    aP = entry;
    zP = aP + entrylen;         // point at last char in identifier

    uStartPage  = 0;
    uPageStep   = 0;
    uStartIndex = 0;
    uStep       = 0;

    u = entrylen;
    while ( u-- )
    {
        uStartPage  = _rotl( uStartPage,  2 ) ^ ( *aP   | 0x20 );
        uStep       = _rotr( uStep,       2 ) ^ ( *aP++ | 0x20 );
        uStartIndex = _rotr( uStartIndex, 2 ) ^ ( *zP   | 0x20 );
        uPageStep   = _rotl( uPageStep,   2 ) ^ ( *zP-- | 0x20 );
    }

    uStartPage %= ndicpages;
    uPageStep  %= ndicpages;
    if ( uPageStep == 0 )
        uPageStep++;
    uStartIndex %= HASHMOD;
    uStep       %= HASHMOD;
    if ( uStep == 0 )
        uStep++;

    uPage = uStartPage;
    uIndex = uStartIndex;

    // number of bytes in entry
    nbytes = 1 + entrylen + 2;
    if (entrylen > 255)
        nbytes += 2;

    while (1)
    {
        aP = &bucketsP[uPage * BUCKETPAGE];
        uStartIndex = uIndex;
        while (1)
        {
            if ( 0 == aP[ uIndex ] )
            {
                // n = next available position in this page
                n = aP[ HASHMOD ] << 1;
                assert(n > HASHMOD);

                // if off end of this page
                if (n + nbytes > BUCKETPAGE )
                {   aP[ HASHMOD ] = 0xFF;
                    break;                      // next page
                }
                else
                {
                    aP[ uIndex ] = n >> 1;
                    memcpy( (aP + n), entry, nbytes );
                    aP[ HASHMOD ] += (nbytes + 1) >> 1;
                    if (aP[HASHMOD] == 0)
                        aP[HASHMOD] = 0xFF;
                    return 1;
                }
            }
            uIndex += uStep;
            uIndex %= 0x25;
            /*if (uIndex > 0x25)
                uIndex -= 0x25;*/
            if( uIndex == uStartIndex )
                break;
        }
        uPage += uPageStep;
        if (uPage >= ndicpages)
            uPage -= ndicpages;
        if( uPage == uStartPage )
            break;
    }