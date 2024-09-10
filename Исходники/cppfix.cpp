void * operator new(size_t size)
{
    return malloc(size);
}