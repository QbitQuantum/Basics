extern DLLSERVER_API bool decompressResource(size32_t len, const void *data, StringBuffer &result)
{
    MemoryBuffer tgt;
    decompressResource(len, data, tgt);
    tgt.append((char)0);
    unsigned expandedLen = tgt.length();
    result.setBuffer(expandedLen, reinterpret_cast<char *>(tgt.detach()), expandedLen-1);
    return true;
}