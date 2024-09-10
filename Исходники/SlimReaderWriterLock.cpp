bool SlimReaderWriterLock::try_lock_shared()
{
   return TryAcquireSRWLockShared( &mSrwlock ) != 0;
}