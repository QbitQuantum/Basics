inline void ReadWriteLockRead(ReadWriteLock* self)
{
  AcquireSRWLockShared(&self->m_Impl);
}