template< class T > void _test()
{
    T* lock = new T;
    lock->set();

#ifdef LUNCHBOX_USE_OPENMP
    const size_t nThreads = LB_MIN( lunchbox::OMP::getNThreads() * 3,
                                    MAXTHREADS );
#else
    const size_t nThreads = 16;
#endif

    Thread< T > threads[MAXTHREADS];
    for( size_t i = 1; i <= nThreads; i = i << 1 )
    {
        _running = true;
        for( size_t j = 0; j < i; ++j )
        {
            threads[j].lock = lock;
            TEST( threads[j].start( ));
        }
        lunchbox::sleep( 10 ); // let threads initialize

        _clock.reset();
        lock->unset();
        lunchbox::sleep( TIME ); // let threads run
        _running = false;

        for( size_t j = 0; j < i; ++j )
            TEST( threads[j].join( ));
        const float time = _clock.getTimef();

        TEST( !lock->isSet( ));
        lock->set();

        size_t ops = 0;
        for( size_t j = 0; j < nThreads; ++j )
            ops += threads[j].ops;

        std::cout << std::setw(20) << lunchbox::className( lock ) << ", "
                  << std::setw(12) << /*set, test, unset*/ 3 * ops / time
                  << ", " << std::setw(3) << i << std::endl;
    }

    delete lock;
}