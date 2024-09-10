void TaskScheduler::enqueueAction(const ros::Time & when,  ActionType type,boost::shared_ptr<ThreadParameters> tp)
{
	ThreadAction ta;
	PRINTF(3,"ea:Locking\n");
	pthread_mutex_lock(&aqMutex);
	PRINTF(3,"ea:Locked\n");
	// if (!runScheduler) return;
	PRINTF(2,"Enqueing action %.3f %s -- %s\n",when.toSec(),actionString(type),
			tp?(tp->task->getName().c_str()):"none");

	ta.type = type;
	ta.tp = tp;
	actionQueue[when.toSec()] = ta;
	PRINTF(3,"ea:Signalling\n");
	pthread_cond_signal(&aqCond);
	PRINTF(3,"ea:Unlocking\n");
	pthread_mutex_unlock(&aqMutex);
}