//-----------------------------------------------------------------------------
// name: cb2()
// desc: ...
//-----------------------------------------------------------------------------
//int Digitalio::cb2( char * buffer, int buffer_size, void * user_data )
int Digitalio::cb2( void *output_buffer, void *input_buffer,
                    unsigned int buffer_size,
                    double streamTime,
                    RtAudioStreamStatus status,
                    void *user_data )
{
    DWORD__ len = buffer_size * sizeof(SAMPLE) * m_num_channels_out;
    Chuck_VM * vm_ref = (Chuck_VM *)user_data;
    
    // priority boost
    if( !m_go && Chuck_VM::our_priority != 0x7fffffff )
    {
#if !defined(__PLATFORM_WIN32__) || defined(__WINDOWS_PTHREAD__)
        g_tid_synthesis = pthread_self();
#else
        // must duplicate for handle to be usable by other threads
        g_tid_synthesis = NULL;
        DuplicateHandle(
            GetCurrentProcess(),
            GetCurrentThread(),
            GetCurrentProcess(),
            &g_tid_synthesis,
            0,
            FALSE,
            DUPLICATE_SAME_ACCESS
        );

        // TODO: close the duplicate handle?
#endif
        Chuck_VM::set_priority( Chuck_VM::our_priority, NULL );
        memset( output_buffer, 0, len );
        m_go = TRUE;

        // start watchdog
        if( g_do_watchdog )
        {
            // timestamp
            g_watchdog_time = get_current_time( TRUE );
            // start watchdog
            watchdog_start();
        }

        // let it go the first time
        return 0;
    }

    // copy input to local buffer
    if( m_num_channels_in )
    {
        memcpy( m_buffer_in, input_buffer, len );
        // copy to extern
        if( m_extern_in ) memcpy( m_extern_in, input_buffer, len );
    }

    // check xrun
    if( m_xrun < 6 )
    {
        // timestamp
        if( g_do_watchdog ) g_watchdog_time = get_current_time( TRUE );
        // get samples from output
        vm_ref->run( buffer_size, m_buffer_in, m_buffer_out );
        // ...
        if( m_xrun ) m_xrun--;
    }
    else
    {
        // reset
        m_xrun /= 2;
    }

    // copy local buffer to be rendered
    if( !m_end ) memcpy( output_buffer, m_buffer_out, len );
    // set all elements of local buffer to silence
    else memset( output_buffer, 0, len );

    // copy to extern
    if( m_extern_out ) memcpy( m_extern_out, output_buffer, len );


    return 0;
}