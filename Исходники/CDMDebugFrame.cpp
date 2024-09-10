int CDMDebugFrame::run() {
	setThreadPriority(Thread::LOW);
	stop = false;

	while(true) {
		s.wait();
		if(stop)
			break;

		unique_ptr<string> x;
		if(!cmdList.pop(x)) {
			continue;
		}
		addLine(*x);
	}
		
	stop = false;
	return 0;
}