_CRTIMP void * __cdecl _recalloc_crt(void *ptr, size_t count, size_t size)
{
    unsigned long WaitTime = 0;
    void *pv;

Retry:
    pv = _recalloc(ptr, count, size);
    if (!pv && size && _maxwait > 0)
    {
        WaitTime = wait_a_bit(WaitTime);
        if (WaitTime != -1)
        {
            goto Retry;
        }
    }
    return pv;
}