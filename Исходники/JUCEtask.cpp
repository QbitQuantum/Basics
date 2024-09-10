void JUCETaskSuspendAll(void)
{
	tasklistmutex.enter();
	JUCETask *thistaskArray[MAX_JUCETASKS];
	for (unsigned int i = 0; i < MAX_JUCETASKS; i++)
	{
		thistaskArray[i] = taskArray[i];		
	}
	tasklistmutex.exit();
	
	for (unsigned int i = 0; i < MAX_JUCETASKS; i++)
	{
		if (thistaskArray[i] != NULL)
		{
			if ( Thread::getCurrentThreadId() != thistaskArray[i]->getThreadId() )
			{
				thistaskArray[i]->stopThread(5000);
			}
			
		}
		
	}
	
}