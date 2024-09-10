 void SimpleRWLock::lock_shared() { 
     AcquireSRWLockShared(&_lock);
 }