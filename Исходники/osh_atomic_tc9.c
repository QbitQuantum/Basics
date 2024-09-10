static int test_item2(void)
{
    int rc = TC_PASS;
    TYPE_VALUE* shmem_addr = NULL;
    TYPE_VALUE my_value = 0;
    TYPE_VALUE expect_value = 0;
    int num_proc = 0;
    int my_proc = 0;
    int peer_proc = 0;
    int i = 0;

    num_proc = _num_pes();
    my_proc = _my_pe();

    shmem_addr = shmalloc(sizeof(*shmem_addr));
    if (shmem_addr)
    {
        TYPE_VALUE value = 0;

        /* Store my value */
        my_value = (TYPE_VALUE)my_proc;
        *shmem_addr = DEFAULT_VALUE;

        /* Define peer */
        peer_proc = (my_proc + 1) % num_proc;

        /* Define expected value */
        expect_value = ( my_proc == 0 ? (num_proc - 1) : (my_proc - 1) ) + (__cycle_count - 1);

        shmem_barrier_all();
        for (i = 0; (i < __cycle_count) && (rc == TC_PASS); i++)
        {
            value = num_proc + __cycle_count;
            value = FUNC_VALUE(shmem_addr, value, (my_value + i), peer_proc);
            if  ( ((i > 0 ) && (value != (my_value + i - 1))) || ((i == 0) && (value != DEFAULT_VALUE)) )
            {
                break;
            }

            value = ( i == 0 ? DEFAULT_VALUE : (my_value + i - 1));
            value = FUNC_VALUE(shmem_addr, value, (my_value + i), peer_proc);
            if  ( ((i > 0 ) && (value != (my_value + i - 1))) || ((i == 0) && (value != DEFAULT_VALUE)) )
            {
                break;
            }
        }
        shmem_barrier_all();

        value = *shmem_addr;
        rc = (expect_value == value ? TC_PASS : TC_FAIL);

        log_debug(OSH_TC, "my(#%d:%lld) expected = %lld vs got = %lld\n",
                           my_proc, (INT64_TYPE)my_value, (INT64_TYPE)expect_value, (INT64_TYPE)value);
    }
    else
    {
        rc = TC_SETUP_FAIL;
    }

    if (shmem_addr)
    {
        shfree(shmem_addr);
    }

    return rc;
}