Mutex::Mutex ( Mutex::TYPE  theMutexType /* = Mutex::RECURSIVE */ )
    : threadIostreamBase (              ),
      mutexType          ( theMutexType )
{
    int mutexAttributeKind;
    int result;

    /* It's not paranoia if the computer is really out to get you... */
    memset ( & getMutexAttributes(), 0, sizeof(pthread_mutexattr_t) );
    memset ( & getMutexData(),       0, sizeof(pthread_mutex_t)     );

    /* Create the Mutex Attributes */
    pthread_mutexattr_init ( & getMutexAttributes() );

    /* Decide how we are configuring it. */
    switch ( theMutexType )
    {
    case Mutex::FAST:
        mutexAttributeKind = PTHREAD_MUTEX_FAST_NP;
        break;

    case Mutex::RECURSIVE:
        mutexAttributeKind = PTHREAD_MUTEX_RECURSIVE_NP;
        break;

    case Mutex::ERROR_CHECK:
        mutexAttributeKind = PTHREAD_MUTEX_ERRORCHECK_NP;
        break;

    default:
        FLUSHALL();
        cerr << "[Mutex:Mutex]  Error:  Bad MutexType value:  "
             << int4(theMutexType) << ".  Defaulting to RECURSIVE Mutex."
             << endl;
        mutexType = Mutex::RECURSIVE;
        mutexAttributeKind = PTHREAD_MUTEX_RECURSIVE_NP;
    }


    /* Configure it appropriately.                  *
     * PTHREAD_MUTEX_SETKIND is defined in Mutex.H. */
    result = PTHREAD_MUTEX_SETKIND ( & getMutexAttributes(),
                                     mutexAttributeKind    );
    switch ( result )
    {
    case 0:  /* It worked */
        break;

    case EINVAL:
        FLUSHALL();
        cerr << "[Mutex:Mutex(Mutex::TYPE)]  Programmer Error:  "
             << "pthread_mutexattr_setkind_np(., " << mutexAttributeKind
             << ") failed with EINVAL.  Attempting to continue as FAST MUTEX."
             << endl;
        mutexType = Mutex::FAST;
        break;

    default:  /* What the hell? */
        FLUSHALL();
        cerr << "[Mutex:Mutex(Mutex::TYPE)]  UNKNOWN Error:  "
             << "pthread_mutexattr_setkind_np(., " << mutexAttributeKind
             << ") failed with: " << result
             << ".  Attempting to continue as FAST MUTEX."
             << endl;
        mutexType = Mutex::FAST;
        break;
    }

    /* And finally, initialize the mutex itself... */
    pthread_mutex_init ( & getMutexData(),
                         (   (result == 0)
                             ? & getMutexAttributes()
                             : (const pthread_mutexattr_t *)NULL ) );
}