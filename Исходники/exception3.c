void *
exceptionedThread(void * arg)
{
    int dummy = 0x1;

    (void) set_terminate(&terminateFunction);

    throw dummy;

    return (void *) 0;
}