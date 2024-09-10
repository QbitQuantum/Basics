/****************************************************************************
 * Place for Test Item functions
 ***************************************************************************/
static int test_item1(void)
{
    int rc = TC_PASS;
    TYPE_VALUE* shmem_addr = NULL;
    TYPE_VALUE* local_addr = NULL;
    TYPE_VALUE my_value = 0;
    TYPE_VALUE peer_value = 0;
    TYPE_VALUE* expect_value = NULL;
    int num_proc = 0;
    int my_proc = 0;
    int peer_proc = 0;
	int tst, sst;
    int max_stride = MAX_ARRAY_SIZE/2-1;

    num_proc = _num_pes();
    my_proc = _my_pe();
    shmem_addr = shmalloc(sizeof(*shmem_addr)*MAX_ARRAY_SIZE);
    local_addr = malloc(sizeof(*local_addr)*MAX_ARRAY_SIZE);
    expect_value = malloc(sizeof(*expect_value)*MAX_ARRAY_SIZE);
    if (shmem_addr)
    {
        INT64_TYPE i = 0;
        INT64_TYPE j = 0;
        int num_to_get;
        my_value = 0;
        size_t odd_pos;
        for (i = 0; (i < COUNT_VALUE) && (rc == TC_PASS); i++)
        {
            tst = (i < max_stride) ? i+1 : max_stride;
            sst = tst;
            num_to_get = MAX_ARRAY_SIZE/tst;
            /* Set my value */
            my_value = (TYPE_VALUE)(my_proc + 1);
            memset(local_addr,0,MAX_ARRAY_SIZE*SIZE_VALUE);
            memset(expect_value,0,MAX_ARRAY_SIZE*SIZE_VALUE);
            for (j = 0; j < MAX_ARRAY_SIZE; j++)
                shmem_addr[j] = my_value;


            /* Define peer and it value */
            peer_proc = (my_proc + 1) % num_proc;
            peer_value = (TYPE_VALUE)(peer_proc + 1);


            /* Define expected value */
            for (j=0; j<num_to_get; j++)
                expect_value[j*tst] = peer_value;
            /* Wait is set instead of barrier to give some time to all PE for setting their values */
            shmem_barrier_all();

            /* Get value from peer */
            FUNC_VALUE(local_addr, shmem_addr,tst,sst,num_to_get,peer_proc);

            if (rc == TC_PASS)
            {
                rc = (compare_buffer((unsigned char*)local_addr, (unsigned char*)expect_value, MAX_ARRAY_SIZE, &odd_pos) ? TC_PASS : TC_FAIL);
            }
            log_debug(OSH_TC, "my(#%d:%lld) peer(#%d:%lld) expected = %lld vs got = %lld\n",
                               my_proc, (INT64_TYPE)my_value, peer_proc, (INT64_TYPE)peer_value, (INT64_TYPE)expect_value[0], (INT64_TYPE)local_addr[0]);

            /* Wait is set instead of barrier to give some time to all PE for setting their values */
            shmem_barrier_all();
        }
    }
    else
    {
        rc = TC_SETUP_FAIL;
    }

    if (local_addr)
    {
        free(local_addr);
    }
    if (expect_value)
    {
        free(expect_value);
    }
    if (shmem_addr)
    {
        shfree(shmem_addr);
    }

    return rc;
}