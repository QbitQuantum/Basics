    // send a condition signal to wake one thread waiting on condition
    // in Win32, this actually wakes up all threads, same as Broadcast
    // use PulseEvent to auto-reset the signal after waking all threads
    void Signal( void )
    {
#if   defined( HAVE_POSIX_THREAD )
      pthread_cond_signal( &mCondition );
#elif defined( HAVE_WIN32_THREAD )
      PulseEvent( mCondition );
#endif
    }