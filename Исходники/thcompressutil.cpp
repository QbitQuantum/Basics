size32_t ThorCompress(const void * src, size32_t srcSz, MemoryBuffer & dest, size32_t threshold)
{
    size32_t prev = dest.length();
    size32_t dSz = srcSz + sizeof(size32_t);
    void * d = dest.reserve(dSz);
    size32_t ret = ThorCompress(src, srcSz, d, dSz, threshold);
    dest.setLength(prev+ret);
    return ret;
}