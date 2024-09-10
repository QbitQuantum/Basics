bool MemPage::extend(RadixHeapBlock *block,ulen blen)
{
    ulen len=block->len;

    blen=Align(blen,Sys::MemPageLen);

    if( blen<=len ) return false;

    if( !Sys::MemPageExtend(block,len/Sys::MemPageLen,(blen-len)/Sys::MemPageLen) ) return false;

    block->init(blen);

    return true;
}