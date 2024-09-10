template< class T, uint32_t hold > void _test()
{
    T* lock = new T;
    lock->set();

#ifdef LUNCHBOX_USE_OPENMP
    const size_t nThreads = LB_MIN( lunchbox::OMP::getNThreads()*3, MAXTHREADS );
#else
    const size_t nThreads = 16;
#endif

    WriteThread< T, hold > writers[MAXTHREADS];
    ReadThread< T, hold > readers[MAXTHREADS];

    std::cout << "               Class, write ops/ms,  read ops/ms, w threads, "
              << "r threads" << std::endl;
    for( size_t nWrite = 0; nWrite <= nThreads;
         nWrite = (nWrite == 0) ? 1 : nWrite << 1 )
    {
        for( size_t i = 1; i <= nThreads; i = i << 1 )
        {
            if( i < nWrite )
                continue;

            const size_t nRead = i - nWrite;
            _running = true;
            for( size_t j = 0; j < nWrite; ++j )
            {
                writers[j].lock = lock;
                TEST( writers[j].start( ));
            }
            for( size_t j = 0; j < nRead; ++j )
            {
                readers[j].lock = lock;
                TESTINFO( readers[j].start(), j );
            }
            lunchbox::sleep( 10 ); // let threads initialize

            _clock.reset();
            lock->unset();
            lunchbox::sleep( TIME ); // let threads run
            _running = false;

            for( size_t j = 0; j < nWrite; ++j )
                TEST( writers[j].join( ));
            for( size_t j = 0; j < nRead; ++j )
                TEST( readers[j].join( ));
            const double time = _clock.getTimed();

            TEST( !lock->isSet( ));
            lock->set();

            size_t nWriteOps = 0;
            double wTime = time * double( nWrite );
            for( size_t j = 0; j < nWrite; ++j )
            {
                nWriteOps += writers[j].ops;
                wTime -= writers[j].sTime;
            }
            if( nWrite > 0 )
                wTime /= double( nWrite );
            if( wTime == 0.f )
                wTime = std::numeric_limits< double >::epsilon();


            size_t nReadOps = 0;
            double rTime = time * double( nRead );
            for( size_t j = 0; j < nRead; ++j )
            {
                nReadOps += readers[j].ops;
                rTime -= readers[j].sTime;
            }
            if( nRead > 0 )
                rTime /= double( nRead );
            if( rTime == 0.f )
                rTime = std::numeric_limits< double >::epsilon();

            std::cout << std::setw(20)<< lunchbox::className( lock ) << ", "
                      << std::setw(12) << 3 * nWriteOps / wTime << ", "
                      << std::setw(12) << 3 * nReadOps / rTime << ", " 
                      << std::setw(9) << nWrite << ", " << std::setw(9) << nRead
                      << std::endl;
        }
    }

    delete lock;
}