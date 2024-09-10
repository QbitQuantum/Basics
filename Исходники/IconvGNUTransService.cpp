// ---------------------------------------------------------------------------
//  IconvGNUTransService: The virtual transcoding service API
// ---------------------------------------------------------------------------
int IconvGNUTransService::compareIString(const XMLCh* const    comp1
                                        , const XMLCh* const    comp2)
{
    const XMLCh* cptr1 = comp1;
    const XMLCh* cptr2 = comp2;

    XMLCh    c1 = toUpper(*cptr1);
    XMLCh    c2 = toUpper(*cptr2);
    while ( (*cptr1 != 0) && (*cptr2 != 0) ) {
        if (c1 != c2)
            break;
        c1 = toUpper(*(++cptr1));
        c2 = toUpper(*(++cptr2));

    }
    return (int) ( c1 - c2 );
}