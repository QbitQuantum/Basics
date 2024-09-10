void deserData(unsigned char *valOut, int len, const unsigned char **data, long *pBlobSizeLeft)
{
    Assert( data && *data && pBlobSizeLeft && (*pBlobSizeLeft>=len) );
    MemMove( valOut, *data, len );
    *data = *data+len;
    *pBlobSizeLeft -= len;
}