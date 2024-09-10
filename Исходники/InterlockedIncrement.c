UINT32
EFIAPI
InternalSyncIncrement (
  IN      volatile UINT32           *Value
  )
{
  return _InterlockedIncrement ((long *)Value);
}