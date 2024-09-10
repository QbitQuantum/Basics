static int test_item4(void)
{
    int rc = TC_PASS;
    TYPE_VALUE* shmem_addr = NULL;
    TYPE_VALUE* recv_addr = NULL;
    TYPE_VALUE my_value = 0;
    TYPE_VALUE peer_value = 0;
    TYPE_VALUE expect_value = 0;
    int num_proc = 0;
    int my_proc = 0;
    int peer_proc = 0;

    num_proc = _num_pes();
    my_proc = _my_pe();

    shmem_addr = (TYPE_VALUE*)shmalloc(sizeof(*shmem_addr) * __max_buffer_size);
    recv_addr = (TYPE_VALUE*)sys_malloc(sizeof(*recv_addr) * __max_buffer_size);
    if (shmem_addr && recv_addr)
    {
        INT64_TYPE i = 0;
        long cur_buf_size = 0;

        my_value = 0;
        for (i = 0; (i < __cycle_count) && (rc == TC_PASS); i++)
        {
            /* Set my value */
            my_value = (my_proc % 2 ? 1 : -1) * (i * (MAX_VALUE / __cycle_count));
            cur_buf_size = sys_max(1, (i + 1) * __max_buffer_size / __cycle_count);
            fill_buffer((void *)shmem_addr, cur_buf_size, (void *)&my_value, sizeof(my_value));

            /* Give some time to all PE for setting their values */
            shmem_barrier_all();

            /* Define peer and it value */
            peer_proc = (my_proc + 1) % num_proc;
            peer_value = (peer_proc % 2 ? 1 : -1) * (i * (MAX_VALUE / __cycle_count));

            /* Define expected value */
            expect_value = peer_value;

            /* Get value from peer */
            FUNC_VALUE(recv_addr, shmem_addr, cur_buf_size, peer_proc);

            rc = (!compare_buffer_with_const(recv_addr, cur_buf_size, &expect_value, sizeof(expect_value)) ? TC_PASS : TC_FAIL);

            log_debug(OSH_TC, "my(#%d:%Lf) peer(#%d:%Lf) expected = %Lf buffer size = %lld\n",
                               my_proc, (long double)my_value, peer_proc, (long double)peer_value, (long double)expect_value, (INT64_TYPE)cur_buf_size);

            if (rc)
            {
                TYPE_VALUE* check_addr = recv_addr;
                int odd_index = compare_buffer_with_const(check_addr, cur_buf_size, &expect_value, sizeof(expect_value));
                int show_index = (odd_index > 1 ? odd_index - 2 : 0);
                int show_size = sizeof(*check_addr) * sys_min(3, cur_buf_size - odd_index - 1);

                log_debug(OSH_TC, "index of incorrect value: 0x%08X (%d)\n", odd_index - 1, odd_index - 1);
                log_debug(OSH_TC, "buffer interval: 0x%08X - 0x%08X\n", show_index, show_index + show_size);
                show_buffer(check_addr + show_index, show_size);
            }

            shmem_barrier_all();
        }
    }
    else
    {
        rc = TC_SETUP_FAIL;
    }

    if (recv_addr)
    {
        sys_free(recv_addr);
    }

    if (shmem_addr)
    {
        shfree(shmem_addr);
    }

    return rc;
}