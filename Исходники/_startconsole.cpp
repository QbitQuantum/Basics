void * __cdecl operator new(unsigned int size,const char *file,int line)
{
    void *p;
    p = _malloc_dbg(size,_NORMAL_BLOCK,file,line);
    MemoryUsedCount+=_msize(p);
    return p;
}