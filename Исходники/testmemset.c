void bulk_test_nb(int iters) {GASNET_BEGIN_FUNCTION();
    int i;
    int64_t begin, end;
    stat_struct_t stput;
    gasnet_handle_t *handles;
    int payload;
    
	handles = (gasnet_handle_t *) test_malloc(sizeof(gasnet_handle_t) * iters);

	for (payload = min_payload; payload <= max_payload && payload > 0; payload *= 2) {
		init_stat(&stput, payload);

		BARRIER();
	
		if (iamsender) {
			/* measure the throughput of sending a message */
			begin = TIME();
			for (i = 0; i < iters; i++) {
				handles[i] = gasnet_memset_nb(peerproc, tgtmem, 0x5a, payload);
			}
			gasnet_wait_syncnb_all(handles, iters);
			end = TIME();
		 	update_stat(&stput, (end - begin), iters);
		}
	
		BARRIER();
       
		if (iamsender) {
			print_stat(myproc, &stput, "memset_nb throughput", PRINT_THROUGHPUT);
		}	
	
	}

	test_free(handles);
}