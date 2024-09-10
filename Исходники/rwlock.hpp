 bool tryrdlock()
 {
     return TryAcquireSRWLockShared(&rwlock_);
 }