Burger::Semaphore::Semaphore(Word32 uCount) :
	m_uCount(uCount)
{
	// Get the maximum semaphores
	Word32 uMax = uCount+32768U;
	// Did it wrap (Overflow?)
	if (uMax<uCount) {
		// Use max
		uMax = BURGER_MAXUINT;
	}
	m_pSemaphore = CreateSemaphoreA(NULL,uCount,uMax,NULL);
}