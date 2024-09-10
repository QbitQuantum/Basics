	void IConcurrentPool::Init()
	{
		mWork = std::make_shared<boost::asio::io_service::work>( mDispatcher );

		const auto f = [ = ]()
		{
			LThreadId = GetCurrentThreadId();

			LThreadCallHistory = std::make_shared<ThreadCallHistory>( LThreadId );
			InterlockedPushEntrySList( &GThreadCallHistory, reinterpret_cast<PSLIST_ENTRY>(LThreadCallHistory.get()) );

			LThreadCallElapsedRecord = std::make_shared<ThreadCallElapsedRecord>( LThreadId );
			InterlockedPushEntrySList( &GThreadCallElapsedRecord, reinterpret_cast<PSLIST_ENTRY>(LThreadCallElapsedRecord.get()) );

			InitThread();
			Run();
		};

		for( std::size_t i = 0; i < mPoolSize; ++i )
		{
			mGroup.create_thread( f );
		}
	}