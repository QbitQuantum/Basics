int
stresscpu_thread_setspecific(stresscpu_thread_key_t    key, 
                             const void *              value)
{
    int ret;

    if(key!=NULL && value != NULL)
    {
        EnterCriticalSection(&key->cs);
        ret = TlsSetValue(key->tls_index,(void *)value);
        LeaveCriticalSection(&key->cs);
    }
    if (ret == 0)
    {
        ret = EAGAIN;
    }
    else
    {
        ret = 0;
    }
    return ret;
}