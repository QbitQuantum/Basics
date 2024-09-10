// Function name	: ShmemLockedQueue::Insert
// Description	    : 
// Return type		: bool 
// Argument         : unsigned char *buffer
// Argument         : unsigned int length
// Argument         : int tag
// Argument         : int from
bool ShmemLockedQueue::Insert(
	unsigned char *buffer, unsigned int length, int tag, int from)
{
	ShmemLockedQueueHeader *pMessage;

	lock(m_plQMutex);

	if (length > m_dwMaxMsgSize)
	{
		unlock(m_plQMutex);
		return false;
	}

	// Wait for a contiguous block large enough to hold the data 
	while ( ( SHMEM_Q_TAIL_PTR >= m_pEnd ) || 
			( (unsigned long)m_pEnd - 
			  (unsigned long)SHMEM_Q_TAIL_PTR - 
			   sizeof(ShmemLockedQueueHeader) < length) )
	{
		unlock(m_plQMutex);
		if (m_pProgressPollFunction)
		{
			while (!test(m_plQEmptyTrigger))
				m_pProgressPollFunction();
		}
		else
			wait(m_plQEmptyTrigger);
		lock(m_plQMutex);
	}

	// Read the tail pointer
	pMessage = SHMEM_Q_TAIL_PTR;
	// If the head offset is 0, set it to the tail
	if ( SHMEM_Q_HEAD_OFFSET == 0 )
		SHMEM_Q_HEAD_OFFSET = SHMEM_Q_TAIL_OFFSET;

	// Set the state and advance the tail offset
	pMessage->state = SHMEM_Q_BEING_WRITTEN;
	// Advance the tail offset
	SHMEM_Q_TAIL_OFFSET = 
		(unsigned long)(
			(unsigned long)pMessage + 
			sizeof(ShmemLockedQueueHeader) + 
			length - (unsigned long)m_pBase);
	unlock(m_plQMutex);

	// Write the header
	pMessage->tag = tag;
	pMessage->from = from;
	pMessage->length = length;
	pMessage->next_offset = (sizeof(ShmemLockedQueueHeader) + length);
	
	// Copy the data
	memcpy((LPBYTE)pMessage + sizeof(ShmemLockedQueueHeader), buffer, length);

	lock(m_plQMutex);
	// Signal data has arrived and release the mutex
	pMessage->state = SHMEM_Q_AVAIL_FOR_READ;
	if (m_bUseEvent)
		SetEvent(m_hMsgAvailableEvent);
	else
		setevent(m_plMsgAvailableTrigger);
	resetevent(m_plQEmptyTrigger);
	unlock(m_plQMutex);

	return true;
}