void LZMACompressToBuffer(MemoryBuffer & out, size32_t len, const void * src)
{
    CLZMA lzma;
    size32_t outbase = out.length();
    size32_t *sz = (size32_t *)out.reserve(len+sizeof(size32_t)*2);
    *sz = len;
    sz++;
    *sz = lzma.compress(src,len,sz+1);
    if (*sz>len) {
        *sz = len;
        memcpy(sz+1,src,len);
    }
    else 
        out.setLength(outbase+sizeof(size32_t)*2+*sz);
}