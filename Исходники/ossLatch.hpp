 BOOLEAN try_lock_shared ()
 {
    return TryAcquireSRWLockShared ( &_lock ) ;
 }