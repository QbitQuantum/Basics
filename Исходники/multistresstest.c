int do_main(void)
#endif
{
/* -------------------------------------------------------------------- */
/*      Our first pass is to establish the correct answers for all      */
/*      the tests.                                                      */
/* -------------------------------------------------------------------- */
    int i, test_count = sizeof(test_list) / sizeof(TestItem); 

    for( i = 0; i < test_count; i++ )
    {
        TestItem *test = test_list + i;

        projPJ src_pj, dst_pj;

        src_pj = custom_pj_init_plus_ctx( pj_get_default_ctx(), test->src_def );
        dst_pj = custom_pj_init_plus_ctx( pj_get_default_ctx(), test->dst_def );

        if( src_pj == NULL )
        {
            printf( "Unable to translate:\n%s\n", test->src_def );
            test->skip = 1;
            continue;
        }

        if( dst_pj == NULL )
        {
            printf( "Unable to translate:\n%s\n", test->dst_def );
            test->skip = 1;
            continue;
        }
        
        test->dst_x = test->src_x;
        test->dst_y = test->src_y;
        test->dst_z = test->src_z;

        test->dst_error = pj_transform( src_pj, dst_pj, 1, 0, 
                                        &(test->dst_x), 
                                        &(test->dst_y),
                                        &(test->dst_z) );
     
        pj_free( src_pj );
        pj_free( dst_pj );

        test->skip = 0;

#ifdef notdef
        printf( "Test %d - output %.14g,%.14g,%g\n", i, test->dst_x, test->dst_y, test->dst_z );
#endif
    }

    printf( "%d tests initialized.\n", test_count );

/* -------------------------------------------------------------------- */
/*      Now launch a bunch of threads to repeat the tests.              */
/* -------------------------------------------------------------------- */
#ifdef _WIN32

	{ //Scoped to workaround lack of c99 support in VS
		HANDLE ahThread[num_threads];

		for( i = 0; i < num_threads; i++ )
		{
			active_thread_count++;

			ahThread[i] = CreateThread(NULL, 0, WinTestThread, NULL, 0, NULL);
			
			if (ahThread[i] == 0)
			{
				printf( "Thread creation failed.");
				return 1;
			}
		}

		printf( "%d test threads launched.\n", num_threads );

		WaitForMultipleObjects(num_threads, ahThread, TRUE, INFINITE);
	}

#else
    {
	pthread_t ahThread[num_threads];
	pthread_attr_t hThreadAttr;

	pthread_attr_init( &hThreadAttr );
	pthread_attr_setdetachstate( &hThreadAttr, PTHREAD_CREATE_DETACHED );

	for( i = 0; i < num_threads; i++ )
	{
		active_thread_count++;

		pthread_create( &(ahThread[i]), &hThreadAttr, 
			PosixTestThread, NULL );
	}

	printf( "%d test threads launched.\n", num_threads );

	while( active_thread_count > 0 )				       
		sleep( 1 );
    }
#endif

    printf( "all tests complete.\n" );

    return 0;
}