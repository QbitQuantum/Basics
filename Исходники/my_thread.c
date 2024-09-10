void my_thread_exit(void *value_ptr)
{
#ifndef _WIN32
    pthread_exit(value_ptr);
#else
    _endthreadex(0);
#endif
}