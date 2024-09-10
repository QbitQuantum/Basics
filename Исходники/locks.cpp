bit OwnedLock::TryLock() const
{
 if (TryEnterCriticalSection((CRITICAL_SECTION*)hand)) return true;
                                                  else return false;	
}