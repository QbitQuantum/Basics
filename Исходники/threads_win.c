int CRYPTO_THREAD_run_once(CRYPTO_ONCE *once, void (*init)(void))
{
    if (InitOnceExecuteOnce(once, once_cb, init, NULL))
        return 1;

    return 0;
}