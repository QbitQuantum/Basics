	bool MScheduler::Init( uint32 numThreads )
	{
		static const uint32 cProcessors = GetCPUThreadCount();
		AX_ASSERT( cProcessors > 0 );

		const uint32 cDesiredThreads = numThreads > 0 ? numThreads : cProcessors;
		const uint32 cThreads = cDesiredThreads >= kMaxWorkers ? kMaxWorkers : cDesiredThreads;

		for( uint32 i = 0; i < cThreads; ++i ) {
#ifdef _MSC_VER
# pragma warning( push )
# pragma warning( disable:4316 ) //object allocated on the heap may not be aligned 64
#endif
			m_pWorkers[ i ] = new LWorker( *this, i );
#ifdef _MSC_VER
# pragma warning( pop )
#endif
			if( !AX_VERIFY_NOT_NULL( m_pWorkers[ i ] ) ) {
				while( i > 0 ) {
					delete m_pWorkers[ i - 1 ];
					--i;
				}

				return false;
			}
		}

#ifdef _WIN32
		// Peg the main thread to one specific processor core for QueryPerformanceCounter() improvement
		SetThreadAffinityMask( GetCurrentThread(), 1<<0 );
#endif

		m_pThreads[ 0 ] = nullptr;
		for( uint32 i = 1; i < cThreads; ++i ) {
			m_pThreads[ i ] = new LWorkerThread( *m_pWorkers[ i ] );
			if( !AX_VERIFY_NOT_NULL( m_pThreads[ i ] ) ) {
				while( i > 0 ) {
					delete m_pThreads[ i - 1 ];
					--i;
				}

				for( i = 0; i < cThreads; ++i ) {
					delete m_pWorkers[ i ];
				}

				return false;
			}

#if AX_THREAD_MODEL == AX_THREAD_MODEL_WINDOWS
			const HANDLE hThread = m_pThreads[ i ]->GetNative_MSWin();
			SetThreadAffinityMask( hThread, DWORD_PTR( 1 )<<i );
#endif
		}

		m_cWorkers = cThreads;

		m_cSleepingWorkers = 0;
		m_bIsQuitting = false;
		m_cFrameChains = 0;
		m_cFrameTasks = 0;
#if !AX_ASYNC_LOCAL_WORK_ENABLED
		m_cSubmittedChains = 0;
#endif
#if !AX_ASYNC_PER_WORKER_IDLE_FLAG_ENABLED
		m_cIdleWorkers = m_cWorkers;
#endif

		AX_MEMORY_BARRIER(); //must be set before threads start (this is just paranoia)

		for( uint32 i = 1; i < cThreads; ++i ) {
			m_pThreads[ i ]->Start();
		}

		return true;
	}