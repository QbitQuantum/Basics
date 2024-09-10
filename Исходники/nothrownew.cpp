void * operator new( size_t cb )
{
    void *res;

    for (;;) {

        //  allocate memory block
        res = malloc(cb);

        //  if successful allocation, return pointer to memory

        if (res)
            break;

        //  call installed new handler
        if (!_callnewh(cb))
            break;

        //  new handler was successful -- try to allocate again
    }

    RTCCALLBACK(_RTC_Allocate_hook, (res, cb, 0));

    return res;
}