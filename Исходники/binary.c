/**
  Remove bytes from the binary.

  \param buf    Initialized binary buffer.
  \param start  Start index of erase.
  \param count  Number of bytes to remove.
*/
void ur_binErase( UBuffer* buf, int start, int count )
{
    if( start >= buf->used )
        return;
    if( (start + count) < buf->used )
    {
        uint8_t* mem = buf->ptr.b + start;
        memMove( mem, mem + count, buf->used - start - count );
        buf->used -= count;
    }
    else
        buf->used = start;
}