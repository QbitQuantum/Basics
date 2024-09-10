static int test_item4(void)
{
    int rc = TC_PASS;
    TYPE_VALUE* shmem_addr = NULL;
    TYPE_VALUE* send_addr = NULL;
    TYPE_VALUE my_value = 0;
    TYPE_VALUE peer_value = 0;
    TYPE_VALUE expect_value = 0;
    int num_proc = 0;
    int my_proc = 0;
    int peer_proc = 0;

    num_proc = _num_pes();
    my_proc = _my_pe();

    shmem_addr = (TYPE_VALUE*)shmalloc(sizeof(*shmem_addr) * __max_buffer_size);
    send_addr = (TYPE_VALUE*)sys_malloc(sizeof(*send_addr) * __max_buffer_size);
    if (shmem_addr && send_addr)
    {
        INT64_TYPE i = 0;
        long cur_buf_size = 0;

        for (i = 0; (i < __cycle_count) && (rc == TC_PASS); i++)
        {
            cur_buf_size = sys_max(1, (i + 1) * __max_buffer_size / __cycle_count);

            /* Set my value */
            my_value = (-1);
            fill_buffer((void *)shmem_addr, cur_buf_size, (void *)&my_value, sizeof(my_value));

            /* Give some time to all PE for setting their values */
            shmem_barrier_all();

            /* Define peer and it value */
            peer_proc = (my_proc + 1) % num_proc;
            peer_value = (peer_proc % 2 ? 1 : -1) * (i * (MAX_VALUE / __cycle_count));
            fill_buffer((void *)send_addr, cur_buf_size, (void *)&peer_value, sizeof(peer_value));

            /* Define expected value */
            expect_value = (my_proc % 2 ? 1 : -1) * (i * (MAX_VALUE / __cycle_count));

            /* Get value put by peer */
            FUNC_VALUE(shmem_addr, send_addr, cur_buf_size, peer_proc);

            /* Get value put by peer:
             * These routines start the remote transfer and may return before the data
             * is delivered to the remote PE
             */
            wait_for_put_completion(peer_proc,10 /* wait for 10 secs */);

            rc = (!compare_buffer_with_const_longdouble(shmem_addr, cur_buf_size, expect_value) ? TC_PASS : TC_FAIL);

            log_debug(OSH_TC, "my(#%d:%Lf) peer(#%d:%Lf) expected = %Lf buffer size = %lld\n",
                               my_proc, (long double)my_value, peer_proc, (long double)peer_value, (long double)expect_value, (INT64_TYPE)1);

            if (rc)
            {
                TYPE_VALUE* check_addr = shmem_addr;
                int odd_index = compare_buffer_with_const_longdouble(check_addr, cur_buf_size, expect_value);
                int show_index = (odd_index > 1 ? odd_index - 2 : 0);
                int show_size = sizeof(*check_addr) * sys_min(3, cur_buf_size - odd_index - 1);

                log_debug(OSH_TC, "index of incorrect value: 0x%08X (%d)\n", odd_index - 1, odd_index - 1);
                log_debug(OSH_TC, "buffer interval: 0x%08X - 0x%08X\n", show_index, show_index + show_size);
                show_buffer(check_addr + show_index, show_size);
            }
        }
    }
    else
    {
        rc = TC_SETUP_FAIL;
    }

    if (send_addr)
    {
        sys_free(send_addr);
    }

    if (shmem_addr)
    {
        shfree(shmem_addr);
    }

    return rc;
}