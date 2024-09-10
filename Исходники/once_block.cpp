BOOST_LOG_API bool once_block_sentry::enter_once_block() const
{
    AcquireSRWLockExclusive(&g_OnceBlockMutex);

    once_block_flag volatile& flag = m_Flag;
    while (flag.status != once_block_flag::initialized)
    {
        if (flag.status == once_block_flag::uninitialized)
        {
            flag.status = once_block_flag::being_initialized;
            ReleaseSRWLockExclusive(&g_OnceBlockMutex);

            // Invoke the initializer block
            return false;
        }
        else
        {
            while (flag.status == once_block_flag::being_initialized)
            {
                BOOST_VERIFY(SleepConditionVariableSRW(
                    &g_OnceBlockCond, &g_OnceBlockMutex, INFINITE, 0));
            }
        }
    }

    ReleaseSRWLockExclusive(&g_OnceBlockMutex);

    return true;
}