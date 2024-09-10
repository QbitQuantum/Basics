    virtual void run() {
	
	int status;

	DPRINTF(("Created Thread %d\n", getProcessId()));

	//---------------------------------------------------------------------
	// Block until all of the crew members are ready.
	//
	_bar->block(_crew->crewSize+1);

	DPRINTF(("Reving Thread %d\n", getProcessId()));

	//---------------------------------------------------------------------
	// Lock the crew mutex
	//
	status = _mutex->lock();
	DPRINTF(("Thread %d got lock\n", getProcessId()));
	assert(status == 0); 

	//---------------------------------------------------------------------
	// There will be no work to do when the crew members are created,
	// so wait for the go signal.
	//
	while(_crew->workCount == 0) {

	    DPRINTF(("Thread %d waiting to go\n", getProcessId()));
	    status = _go->wait(_mutex);
	    assert(status == 0); 

	    DPRINTF(("Thread %d going\n", getProcessId()));
	}	

        //---------------------------------------------------------------------
	// unlock the crew mutex.
	//
	status = _mutex->unlock();
	assert(status == 0); 


	//---------------------------------------------------------------------
	// While there's work to do, do it !
	// 
	while(true) {

	    DPRINTF(("Thread %d entered while loop.\n", getProcessId()));

	    //-----------------------------------------------------------------
	    // Lock the crew mutex
	    //
	    status = _mutex->lock();
	    assert(status == 0); 
	    
	    //-----------------------------------------------------------------
	    // Wait while there is nothing to do. If _crew->first == 0, 
	    // there's no work.  But if _crew->workCount == 0, we're done.
	    //
	    while(_crew->first == 0) {

		DPRINTF(("Thread %d waiting for work\n", getProcessId()));
		
		status = _go->wait(_mutex);
		assert(status == 0); 

		DPRINTF(("Thread %d woke, %#lx, %d\n",
			 getProcessId(), _crew->first, _crew->workCount));
	    }
	    	   
	    //-----------------------------------------------------------------
	    // Remove and process a work item.
	    //
	    _work = _crew->first;
	    _crew->first = _work->next;
	    if(_crew->first == 0) {
		_crew->last = 0;
	    };

	    DPRINTF(("Thread %d took, %#lx, leaves first %#lx, last %#lx\n",
		   getProcessId(), _work, _crew->first, _crew->last));

	    //-----------------------------------------------------------------
	    // unlock the crew mutex.
	    //
	    status = _mutex->unlock();
	    assert(status == 0); 
	    
	    //-----------------------------------------------------------------
	    // Okay, we have a work item, process it.
	    //
	    float proc_result = pr_processWork();

	    //-----------------------------------------------------------------
	    // Lock the crew mutex to decrement the work count, and
	    // update the result.
	    //
	    status = _mutex->lock();
	    assert(status == 0); 
   
	    *(_result) += proc_result;

	    --_crew->workCount;

	    DPRINTF(("Thread %d decremented work count to %d\n",
		   getProcessId(), _crew->workCount));
	    
	    if(_crew->workCount <= 0) {
		DPRINTF(("Thread %d done.\n", getProcessId()));
	    
		//-------------------------------------------------------------
		// Signal that we have finished our job.
		//
		status = _done->broadcast();
		assert(status == 0); 
	    
		//-------------------------------------------------------------
		// unlock the crew mutex.
		//
		status = _mutex->unlock();	
		assert(status == 0);
		
		break;
	    }

	    //----------------------------------------------------------------
	    // unlock the crew mutex.
	    //
	    status = _mutex->unlock();    
	    assert(status == 0); 
	    
	}

    };