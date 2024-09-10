// TODO: Should have a flag to tell the garbage collector to automatically determine how many iterations are needed
//       It should then gather statistics such as how many objects has been created since last run, and how many objects
//       are destroyed per iteration, and how many objects are detected as cyclic garbage per iteration.
//       It should try to reach a stable number of objects, i.e. so that on average the number of objects added to 
//       the garbage collector is the same as the number of objects destroyed. And it should try to minimize the number
//       of iterations of detections that must be executed per cycle while still identifying the cyclic garbage
//       These variables should also be available for inspection through the gcstatistics.
int asCGarbageCollector::GarbageCollect(asDWORD flags, asUINT iterations)
{
	// If the GC is already processing in another thread, then don't enter here again
	if( TRYENTERCRITICALSECTION(gcCollecting) )
	{
		// If the GC is already processing in this thread, then don't enter here again
		if( isProcessing ) 
		{	
			LEAVECRITICALSECTION(gcCollecting);
			return 1;
		}

		isProcessing = true;

		bool doDetect  = (flags & asGC_DETECT_GARBAGE)  || !(flags & asGC_DESTROY_GARBAGE);
		bool doDestroy = (flags & asGC_DESTROY_GARBAGE) || !(flags & asGC_DETECT_GARBAGE);

		if( flags & asGC_FULL_CYCLE )
		{
			// Reset the state
			if( doDetect )
			{
				// Move all new objects to the old list, so we guarantee that all is detected
				MoveAllObjectsToOldList();
				detectState  = clearCounters_init;
			}
			if( doDestroy )
			{
				destroyNewState = destroyGarbage_init;
				destroyOldState = destroyGarbage_init;
			}

			// The full cycle only works with the objects in the old list so that the
			// set of objects scanned for garbage is fixed even if new objects are added
			// by other threads in parallel.
			unsigned int count = (unsigned int)(gcOldObjects.GetLength());
			for(;;)
			{
				// Detect all garbage with cyclic references
				if( doDetect )
					while( IdentifyGarbageWithCyclicRefs() == 1 ) {}

				// Now destroy all known garbage
				if( doDestroy )
				{
					if( !doDetect )
						while( DestroyNewGarbage() == 1 ) {}
					while( DestroyOldGarbage() == 1 ) {}
				}

				// Run another iteration if any garbage was destroyed
				if( count != (unsigned int)(gcOldObjects.GetLength()) )
					count = (unsigned int)(gcOldObjects.GetLength());
				else
					break;
			}

			isProcessing = false;
			LEAVECRITICALSECTION(gcCollecting);
			return 0;
		}
		else
		{
			while( iterations-- > 0 )
			{
				// Destroy the garbage that we know of
				if( doDestroy )
				{
					DestroyNewGarbage();
					DestroyOldGarbage();
				}

				// Run another incremental step of the identification of cyclic references
				if( doDetect && gcOldObjects.GetLength() > 0 )
					IdentifyGarbageWithCyclicRefs();
			}
		}

		isProcessing = false;
		LEAVECRITICALSECTION(gcCollecting);
	}
	
	// Return 1 to indicate that the cycle wasn't finished
	return 1;
}