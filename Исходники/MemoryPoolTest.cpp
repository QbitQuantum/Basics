void TestSpeed(ScopedLogMessage& msg)
{
ElapsedTimeRec timeRec[3];

	msg.Message("--- TestSpeed ---");

	int numMaxAlloc = kNumMaxAlloc_Speed;
	{	// adjust number of max allocation for low memory machine
		bool memoryAvailable = false;
		char* tempPtr = NULL;

#if defined(POCO_OS_FAMILY_WINDOWS)
		_set_new_handler(ThrowBadAlloc);
#endif

		while(!memoryAvailable)
		{
			try
			{
				tempPtr = new char [kBlockSize * numMaxAlloc];
				memoryAvailable = true;
			}
			catch(...)
			{
				numMaxAlloc /= 2;
			}
			delete [] tempPtr;
			tempPtr = NULL;
		}
		msg.Message(Poco::format(" number of allocation blocks = %d", numMaxAlloc));
	}

	{
		msg.Message(" measuring new/delete...");
		MeasureAllocDeallocTime<Poco::Void> measure(timeRec[0], kBlockSize, 0, numMaxAlloc);
	}
	{
		msg.Message(Poco::format(" measuring Poco::MemoryPool(%z, %d, %d)..."
								, kBlockSize
								, 0
								, numMaxAlloc));
		MeasureAllocDeallocTime<Poco::MemoryPool>
			measure(timeRec[1], kBlockSize, 0, numMaxAlloc);
	}
	{
		msg.Message(Poco::format(" measuring Poco::MemoryPool(%z, %d, %d)..."
								, kBlockSize
								, numMaxAlloc
								, numMaxAlloc));
		MeasureAllocDeallocTime<Poco::MemoryPool>
			measure(timeRec[2], kBlockSize, numMaxAlloc, numMaxAlloc);
	}

	msg.Message("                 new/delete   non pre-allocated   pre-allocated");
	msg.Message("================================================================");
	msg.Message(Poco::format("  init          %8.3fmSec    %8.3fmSec      %8.3fmSec"
								, timeRec[0].timeInit
								, timeRec[1].timeInit
								, timeRec[2].timeInit));
	for(std::size_t loop=0; loop<kNumLoop; ++loop)
	{
		msg.Message(Poco::format("  allocate #%z   %8.3fmSec    %8.3fmSec      %8.3fmSec"
								, loop+1
								, timeRec[0].timeAlloc[loop]
								, timeRec[1].timeAlloc[loop]
								, timeRec[2].timeAlloc[loop]));
		msg.Message(Poco::format("deallocate #%z   %8.3fmSec    %8.3fmSec      %8.3fmSec"
								, loop+1
								, timeRec[0].timeDealloc[loop]
								, timeRec[1].timeDealloc[loop]
								, timeRec[2].timeDealloc[loop]));
	}
	msg.Message(Poco::format("  cleanup       %8.3fmSec    %8.3fmSec      %8.3fmSec"
								, timeRec[0].timeCleanup
								, timeRec[1].timeCleanup
								, timeRec[2].timeCleanup));
	msg.Message("================================================================");
	msg.Message(Poco::format("  total time    %8.3fmSec    %8.3fmSec      %8.3fmSec"
								, timeRec[0].timeTotal
								, timeRec[1].timeTotal
								, timeRec[2].timeTotal));
}