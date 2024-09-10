//Deryabin Andrew: vst chunks support
template <typename T> void
rdwr_writeRaw(T fd, std::vector<char> rawdata, const char *file, int line)
{
    unsigned long complen = compressBound(rawdata.size());
    char *compressed = new char [complen];
    if(!compressed)
    {
        fprintf(stderr, "Failed to allocate %lu bytes of memory at %s:%d\n", complen, file, line);
        throw RemotePluginClosedException();
    }

    std::vector<char>::pointer ptr = &rawdata [0];

    if(compress2((Bytef *)compressed, &complen, (Bytef *)ptr, rawdata.size(), 9) != Z_OK)
    {
        delete compressed;
        fprintf(stderr, "Failed to compress source buffer at %s:%d\n", file, line);
        throw RemotePluginClosedException();
    }

    fprintf(stderr, "compressed source buffer. size=%lu bytes\n", complen);

    int len = complen;
    rdwr_tryWrite(fd, &len, sizeof(int), file, line);
    len = rawdata.size();
    rdwr_tryWrite(fd, &len, sizeof(int), file, line);    
    rdwr_tryWrite(fd, compressed, complen, file, line);

    delete [] compressed;
}