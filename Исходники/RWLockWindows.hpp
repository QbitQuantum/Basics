 bool tryLockRead()
 {
     return TryAcquireSRWLockShared(&this->_rwlock) != 0;
 }