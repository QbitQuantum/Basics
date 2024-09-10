bool DOM::operator==( const DOMString &a, const char *b )
{
    unsigned int blen = strlen(b);
    if(a.length() != blen) return false;

    const QChar* aptr = a.stringPtr();
    while( blen-- ) {
        if((*aptr++).latin1() != *b++)
            return false;
    }

    return true;
}