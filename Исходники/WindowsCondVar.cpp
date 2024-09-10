 bool			WindowsCondVar::notify(bool lock)
 {
   if (lock)
     ownLock();
   WakeConditionVariable(&_condvar);
   if (lock)
     ownUnlock();
   return (true);
 }