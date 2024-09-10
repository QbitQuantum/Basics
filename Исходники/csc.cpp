uint64_t GetFileSize(FILE *f) 
{
    uint64_t size;
    _fseeki64(f, 0, SEEK_END);
    size = _ftelli64(f);
    _fseeki64(f, 0, SEEK_SET);
    return size;
}