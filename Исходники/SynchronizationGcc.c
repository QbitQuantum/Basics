EFIAPI
InitializeSpinLock (
  OUT      SPIN_LOCK                 *SpinLock
  )
{
  ASSERT (SpinLock != NULL);

  _ReadWriteBarrier();
  *SpinLock = SPIN_LOCK_RELEASED;
  _ReadWriteBarrier();

  return SpinLock;
}