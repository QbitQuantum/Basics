static int test_item8(void)
{
    int rc = TC_PASS;
    static TYPE_VALUE target_addr[MAX_BUFFER_SIZE];
    static TYPE_VALUE source_addr[MAX_BUFFER_SIZE];
    TYPE_VALUE source_value = 0;
    TYPE_VALUE expect_value = 0;
    int num_proc = 0;
    int my_proc = 0;

    num_proc = _num_pes();
    my_proc = _my_pe();

    {
        TYPE_VALUE value = DEFAULT_VALUE;
        int i = 0;
        int j = 0;
        long cur_buf_size = 0;

        for (i = 0; (i < __cycle_count) && (rc == TC_PASS); i++)
        {
            cur_buf_size = sys_max(1, (i + 1) * MAX_BUFFER_SIZE / __cycle_count);
            pWrk = shmalloc(sizeof(*pWrk) * sys_max(cur_buf_size/2 + 1, _SHMEM_REDUCE_MIN_WRKDATA_SIZE));
            if (pWrk)
            {
                /* Set initial target value */
                value = DEFAULT_VALUE;
                fill_buffer((void *)target_addr, cur_buf_size, (void *)&value, sizeof(value));

                /* Give some time to all PE for setting their values */
                shmem_barrier_all();

                /* Set my value */
                source_value = (TYPE_VALUE)(my_proc + 1);
                fill_buffer((void *)source_addr, cur_buf_size, (void *)&source_value, sizeof(source_value));

                /* Define expected value */
                expect_value = 0;
                if (my_proc % 2)    expect_value = DEFAULT_VALUE;
                else
                {
                    int k = num_proc;
                    while (k)
                    {
                        if (k % 2)  expect_value |= k;
                        k--;
                    }
                }

                /* This guarantees that PE set initial value before peer change one */
                for ( j = 0; j < _SHMEM_REDUCE_SYNC_SIZE; j++ )
                {
                    pSync[j] = _SHMEM_SYNC_VALUE;
                }
                shmem_barrier_all();

                int in_active_set = check_within_active_set(0, 1, ((num_proc / 2) + (num_proc % 2)), my_proc, num_proc);

                if ( in_active_set ) {
                    /* Put value to peer */
                    FUNC_VALUE(target_addr, source_addr, cur_buf_size, 0, 1, ((num_proc / 2) + (num_proc % 2)), pWrk, pSync);
                }

                /* Get value put by peer:
                 * These routines start the remote transfer and may return before the data
                 * is delivered to the remote PE
                 */
                shmem_barrier_all();
                {
                    int wait = WAIT_COUNT;

                    while (wait--)
                    {
                        value = *target_addr;
                        if (expect_value == value) break;
                        sleep(1);
                    }
                }

                if ( in_active_set ) {
                    rc = (!compare_buffer_with_const(target_addr, cur_buf_size, &expect_value, sizeof(expect_value)) ? TC_PASS : TC_FAIL);

                    log_debug(OSH_TC, "my#%d source = %lld expected = %lld actual = %lld buffer size = %lld\n",
                                       my_proc, (INT64_TYPE)source_value, (INT64_TYPE)expect_value, (INT64_TYPE)value, (INT64_TYPE)cur_buf_size);

                    if (rc)
                    {
                        TYPE_VALUE* check_addr = target_addr;
                        int odd_index = compare_buffer_with_const(check_addr, cur_buf_size, &expect_value, sizeof(expect_value));
                        int show_index = (odd_index > 1 ? odd_index - 2 : 0);
                        int show_size = sizeof(*check_addr) * sys_min(3, cur_buf_size - odd_index - 1);

                        log_debug(OSH_TC, "index of incorrect value: 0x%08X (%d)\n", odd_index - 1, odd_index - 1);
                        log_debug(OSH_TC, "buffer interval: 0x%08X - 0x%08X\n", show_index, show_index + show_size);
                        show_buffer(check_addr + show_index, show_size);
                    }
                }
                shfree(pWrk);
            } else {
                rc = TC_SETUP_FAIL;
            }
        }
    }

    return rc;
}