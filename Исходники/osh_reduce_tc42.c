static int test_item6(void)
{
    int rc = TC_PASS;
    TYPE_VALUE* target_addr = NULL;
    TYPE_VALUE* source_addr = NULL;
    TYPE_VALUE source_value = 0;
    TYPE_VALUE expect_value = 0;
    int num_proc = 0;
    int my_proc = 0;

    num_proc = _num_pes();
    my_proc = _my_pe();

    target_addr = (TYPE_VALUE*)shmalloc(sizeof(*target_addr) * __max_buffer_size);
    source_addr = (TYPE_VALUE*)shmalloc(sizeof(*source_addr) * __max_buffer_size);
    if (target_addr && source_addr)
    {
        TYPE_VALUE value = DEFAULT_VALUE;
        int i = 0;
        int j = 0;
        long cur_buf_size = 0;

        for (i = 0; (i < __cycle_count) && (rc == TC_PASS); i++)
        {
            cur_buf_size = sys_max(1, (i + 1) * __max_buffer_size / __cycle_count);
            pWrk = shmalloc(sizeof(*pWrk) * sys_max(cur_buf_size/2 + 1, _SHMEM_REDUCE_MIN_WRKDATA_SIZE));
            if (pWrk)
            {
                /* Set initial target value */
                value = DEFAULT_VALUE;
                fill_buffer((void *)target_addr, cur_buf_size, (void *)&value, sizeof(value));

                /* Give some time to all PE for setting their values */
                shmem_barrier_all();

                /* Set my value */
                source_value = ( my_proc < OVERFLOW_FACTORIAL_LIMIT ? (TYPE_VALUE)(my_proc + 1) : 1);
                fill_buffer((void *)source_addr, cur_buf_size, (void *)&source_value, sizeof(source_value));

                /* Define expected value */
                expect_value = 1;
                {
                    int k = ( num_proc <= OVERFLOW_FACTORIAL_LIMIT ? num_proc : OVERFLOW_FACTORIAL_LIMIT);
                    while (k) expect_value *= k--;
                }

                /* This guarantees that PE set initial value before peer change one */
                for ( j = 0; j < _SHMEM_REDUCE_SYNC_SIZE; j++ )
                {
                    pSync[j] = _SHMEM_SYNC_VALUE;
                }
                shmem_barrier_all();

                /* Put value to peer */
                FUNC_VALUE(target_addr, source_addr, cur_buf_size, 0, 0, num_proc, pWrk, pSync);

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
                        if (sys_fcompare(expect_value, value)) break;
                        sleep(1);
                    }
                }

                rc = (!compare_buffer_with_const_longdouble(target_addr, cur_buf_size, expect_value) ? TC_PASS : TC_FAIL);

                log_debug(OSH_TC, "my#%d source = %Lf expected = %Lf actual = %Lf buffer size = %lld\n",
                                   my_proc, (long double)source_value, (long double)expect_value, (long double)value, (INT64_TYPE)cur_buf_size);

                if (rc)
                {
                    TYPE_VALUE* check_addr = target_addr;
                    int odd_index = compare_buffer_with_const_longdouble(check_addr, cur_buf_size, expect_value);
                    int show_index = (odd_index > 1 ? odd_index - 2 : 0);
                    int show_size = sizeof(*check_addr) * sys_min(3, cur_buf_size - odd_index - 1);

                    log_debug(OSH_TC, "index of incorrect value: 0x%08X (%d)\n", odd_index - 1, odd_index - 1);
                    log_debug(OSH_TC, "buffer interval: 0x%08X - 0x%08X\n", show_index, show_index + show_size);
                    show_buffer(check_addr + show_index, show_size);
                }

                shfree(pWrk);
            } else {
                rc = TC_SETUP_FAIL;
            }
        }
    }
    else
    {
        rc = TC_SETUP_FAIL;
    }

    if (source_addr)
    {
        shfree(source_addr);
    }

    if (target_addr)
    {
        shfree(target_addr);
    }

    return rc;
}