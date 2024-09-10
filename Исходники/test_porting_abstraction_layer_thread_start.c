  int test_pal_thread_start( test_pal_thread_state_t *thread_state,
                             struct test_pal_logical_processor *lp, 
                             test_pal_thread_return_t (TEST_PAL_CALLING_CONVENTION *thread_function)(void *thread_user_state),
                             void *thread_user_state )
  {
    BOOL
      brv;

    DWORD
      thread_id;

    GROUP_AFFINITY
      ga;

    int
      rv = 0;

    LPPROC_THREAD_ATTRIBUTE_LIST
      attribute_list;

    SIZE_T
      attribute_list_length;

    assert( thread_state != NULL );
    assert( lp != NULL );
    assert( thread_function != NULL );
    // TRD : thread_user_state can be NULL

    /* TRD : here we're using CreateRemoteThreadEx() to start a thread in our own process
             we do this because as a function, it allows us to specify processor and processor group affinity in the create call
    */

    brv = InitializeProcThreadAttributeList( NULL, 1, 0, &attribute_list_length );
    attribute_list = malloc( attribute_list_length );
    brv = InitializeProcThreadAttributeList( attribute_list, 1, 0, &attribute_list_length );

    ga.Mask = ( (KAFFINITY) 1 << lp->logical_processor_number );
    ga.Group = (WORD) lp->windows_logical_processor_group_number;
    memset( ga.Reserved, 0, sizeof(WORD) * 3 );

    brv = UpdateProcThreadAttribute( attribute_list, 0, PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY, &ga, sizeof(GROUP_AFFINITY), NULL, NULL );
    *thread_state = CreateRemoteThreadEx( GetCurrentProcess(), NULL, 0, thread_function, thread_user_state, NO_FLAGS, attribute_list, &thread_id );

    DeleteProcThreadAttributeList( attribute_list );
    free( attribute_list );

    if( *thread_state != NULL )
      rv = 1;

    return( rv );
  }