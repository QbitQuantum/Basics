void oneway_nb_test(int iters, int nbytes, int alignment)
{GASNET_BEGIN_FUNCTION();
    int i;
    int64_t begin, end;
    stat_struct_t st;
    gasnet_handle_t *handles;
    int pad = (alignment % PAGESZ);

	/* initialize statistics */
	init_stat(&st, nbytes, alignment);
	
	handles = (gasnet_handle_t*) test_malloc(sizeof(gasnet_handle_t) * iters);
	
	memset(locbuf+pad, 1, nbytes);

	BARRIER();
	
	if (iamsender) {
		/* measure the throughput of sending a message */
		begin = TIME();
                for (i = 0; i < iters; i++) {
                        handles[i] = gasnet_put_nb_bulk(peerproc, rembuf, locbuf+pad, nbytes);
                }
		gasnet_wait_syncnb_all(handles, iters); 
		end = TIME();
	 	update_stat(&st, (end - begin), iters);
	}
	
	BARRIER();
	
	if (iamsender) {
		print_stat(myproc, &st, "put_nb_bulk throughput", PRINT_THROUGHPUT);
	}	
	
	/* initialize statistics */
	init_stat(&st, nbytes, alignment);

	if (iamsender) {
		/* measure the throughput of receiving a message */
		begin = TIME();
                for (i = 0; i < iters; i++) {
                    handles[i] = gasnet_get_nb_bulk(locbuf, peerproc, rembuf+pad, nbytes);
                } 
		gasnet_wait_syncnb_all(handles, iters); 
		end = TIME();
	 	update_stat(&st, (end - begin), iters);
	}
	
	BARRIER();
	
	if (iamsender) {
		print_stat(myproc, &st, "get_nb_bulk throughput", PRINT_THROUGHPUT);
	}	
	
	test_free(handles);
}