bool ofxTimeMeasurements::startMeasuring(const string & ID, bool accumulate, bool ifClause){

	string localID = ID;
	if (!enabled) return true;

	uint64_t wastedTime;
	if(internalBenchmark){
		wastedTime = TM_GET_MICROS();
	}

	if (!settingsLoaded){
		loadSettings();
		settingsLoaded = true;
	}

	string threadName = "Thread";
	ThreadId thread = getThreadID();
	bool bIsMainThread = isMainThread(thread);

	if(!bIsMainThread){
		if(Poco::Thread::current()){
			threadName = Poco::Thread::current()->getName();
		}
	}

	mutex.lock();

	unordered_map<ThreadId, ThreadInfo>::iterator threadIt = threadInfo.find(thread);
	ThreadInfo * tinfo = NULL;
	core::tree<string> *tr = NULL;

	bool newThread = threadIt == threadInfo.end();

	if (newThread){ //new thread!

		//cout << "NewThread! " << ID << " " << &thread << endl;
		threadInfo[thread] = ThreadInfo();
		tinfo = &threadInfo[thread];
		tr = &tinfo->tree; //easier to read, tr is our tree from now on

		if (!bIsMainThread){
			tinfo->color = threadColorTable[numThreads%(threadColorTable.size())];
			numThreads++;
		}else{ //main thread
			tinfo->color = hilightColor;
		}
		tinfo->order = numThreads;

		string tName = bIsMainThread ? "Main Thread" : ("T" + ofToString(tinfo->order) + ": " + threadName);
		//init the iterator
		*tr = tName; //thread name is root
		tinfo->tit = (core::tree<string>::iterator)*tr;

	}else{
		tinfo = &threadIt->second;
		tr = &(tinfo->tree); //easier to read, tr is our tree from now on
	}

	if(tinfo->order > 0){
		localID = "T" + ofToString(tinfo->order) + ":" + localID;
	}

	//see if we had an actual measurement, or its a new one
	unordered_map<string, TimeMeasurement*>::iterator tit = times.find(localID);
	TimeMeasurement* t;

	if(tit == times.end()){ //if it wasnt in the tree, append it
		times[localID] = t = new TimeMeasurement();
		unordered_map<string, TimeMeasurementSettings>::iterator it2 = settings.find(localID);
		if (it2 != settings.end()){
			t->settings = settings[localID];
			if(tinfo->tit.out() == tinfo->tit.end()){ //if we are the tree root - we cant be hidden!
				t->settings.visible = true;
			}
		}
		tinfo->tit = tinfo->tit.push_back(localID);

	}else{
		core::tree<string>::iterator temptit = tr->tree_find_depth(localID);
		if(temptit != tr->end()){
			tinfo->tit = temptit;
		}else{
			//cout << "gotcha!" << endl;
			//this is the rare case where we already had a measurement for this ID,
			//but it must be assigned to another old thread bc we cant find it!
			//so we re-add that ID for this thread and update the tree iterator
			tinfo->tit = tinfo->tit.push_back(localID);
		}
		t = tit->second;
	}

	t->key = localID;
	t->life = 1.0f; //
	t->measuring = true;
	t->ifClause = ifClause;
	t->microsecondsStop = 0;
	t->accumulating = accumulate;
	if(accumulate) t->numAccumulations++;
	t->error = false;
	t->frame = currentFrameNum;
	t->updatedLastFrame = true;
	t->microsecondsStart = TM_GET_MICROS();
	t->thread = thread;

	mutex.unlock();

	if(internalBenchmark){
		wastedTimeThisFrame += t->microsecondsStart - wastedTime;
	}

	return t->settings.enabled;
}