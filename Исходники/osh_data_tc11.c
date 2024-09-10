static int test_item3(void)
{
    int rc = TC_PASS;
    TYPE_VALUE* shmem_addr = NULL;
    TYPE_VALUE my_value = 0;
    TYPE_VALUE peer_value = 0;
    TYPE_VALUE expect_value = 0;
    int num_proc = 0;
    int my_proc = 0;
    int peer_proc = 0;

    num_proc = _num_pes();
    my_proc = _my_pe();

    shmem_addr = shmalloc(sizeof(*shmem_addr));
    if (shmem_addr)
    {
        TYPE_VALUE value = -1;
        INT64_TYPE i = 0;

        /* Set my value */
        my_value = (-1);
        *shmem_addr = my_value;
        for (i = 0; i < COUNT_VALUE; i++)
        {
            /* Define peer and it value */
            peer_proc = (my_proc + 1) % num_proc;
            peer_value = (peer_proc % 2 ? 1 : -1) * (i * STEP_VALUE);

            /* Define expected value */
            expect_value = (my_proc % 2 ? 1 : -1) * (i * STEP_VALUE);

            /* This guarantees that PE set initial value before peer change one */
            shmem_barrier_all();

            /* Write value to peer */
            FUNC_VALUE(shmem_addr, peer_value, peer_proc);

            /* Get value put by peer:
             * These routines start the remote transfer and may return before the data
             * is delivered to the remote PE
             */
            wait_for_put_completion(peer_proc,10 /* wait for 10 secs */);
            value = *shmem_addr;

            rc = (sys_fcompare(expect_value, value) ? TC_PASS : TC_FAIL);

            log_debug(OSH_TC, "my(#%d:%Lf) peer(#%d:%Lf) expected = %Lf vs got = %Lf\n",
                               my_proc, (long double)my_value, peer_proc, (long double)peer_value, (long double)expect_value, (long double)value);
        }
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