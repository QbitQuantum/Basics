static int test_item3(void)
{
    int rc = TC_PASS;
    TYPE_VALUE* shmem_addr = NULL;
    TYPE_VALUE my_value = 0;
    TYPE_VALUE* check_arr = NULL;
    int num_proc = 0;
    int my_proc = 0;
    int peer_proc = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int flag = 0;
    int missed_values = 0;
    static long* pSync = NULL;

    num_proc = _num_pes();
    my_proc = _my_pe();

    shmem_addr = shmalloc(sizeof(*shmem_addr));
    check_arr = shmalloc(sizeof(*check_arr) * num_proc);

    pSync = shmalloc(sizeof(*pSync) * _SHMEM_COLLECT_SYNC_SIZE);
    for (i = 0; i < _SHMEM_COLLECT_SYNC_SIZE; i++) {
        pSync[i] = _SHMEM_SYNC_VALUE;
    }

    if (shmem_addr && pSync && check_arr)
    {
        static TYPE_VALUE value = 0;

        /* Store my value */
        my_value = (TYPE_VALUE)my_proc;
        *shmem_addr = DEFAULT_VALUE;

        shmem_barrier_all();
        for (i = 0; (i < __cycle_count) && (rc == TC_PASS); i++)
        {
            missed_values = 0;
            my_value = (TYPE_VALUE)my_proc;

            value = FUNC_VALUE(shmem_addr, my_value, peer_proc);

            shmem_barrier_all();
            shmem_collect32(check_arr, &value, (sizeof(value) + 3 ) / 4, 0, 0, num_proc, pSync);
            shmem_barrier_all();
            for (j = 0; j < num_proc ; j++)
            {
                flag = 0;
                for (k = 0; k < num_proc; k++)
                {
                    if (sys_fcompare(check_arr[k], j))
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    missed_values++;
                }
                if (missed_values > 1)
                {
                    rc = TC_FAIL;
                    break;
                }
            }
        }
        shmem_barrier_all();

        log_debug(OSH_TC, "my(#%d:%lld) missed_values expected = 1 vs missed_values = %d\n",
                           my_proc, (INT64_TYPE)my_value, missed_values);
    }
    else
    {
        rc = TC_SETUP_FAIL;
    }

    if (shmem_addr)
    {
        shfree(shmem_addr);
    }
    if (pSync)
    {
        shfree(pSync);
    }

    return rc;
}