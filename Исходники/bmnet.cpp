void MyThread::monitorTimeout(){
	STOP_TIMER(monitorTimer);
	if(terminateFlag)
		terminateThread();
	else
	{
		monitorTimer->start(10);
	}
}