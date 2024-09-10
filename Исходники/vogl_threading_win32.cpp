 semaphore::semaphore(int32 initialCount, int32 maximumCount, const char *pName)
 {
     m_handle = CreateSemaphoreA(NULL, initialCount, maximumCount, pName);
     if (NULL == m_handle)
     {
         VOGL_FAIL("semaphore: CreateSemaphore() failed");
     }
 }