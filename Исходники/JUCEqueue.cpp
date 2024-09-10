CriticalSection *MutexList_GetPointer(int mutexID)
{
	queuelistmutex.enter();
	MutexList_t *temp = MutexList;
	CriticalSection *returnPointer = NULL;
	
	while (temp != NULL)
	{
		if (temp->mutexID == mutexID)
		{
			returnPointer = temp->mutexPointer;
			break;
		}
		
		temp = temp->next;
	}
	
	queuelistmutex.exit();
	return returnPointer;
	
}