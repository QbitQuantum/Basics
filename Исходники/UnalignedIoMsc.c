/**
  Reads a 32-bit word from the specified, possibly unaligned I/O-type address.

  Reads the 32-bit I/O port specified by Port. The 32-bit read value is
  returned. This function must guarantee that all I/O read and write operations
  are serialized.

  If 32-bit unaligned I/O port operations are not supported, then ASSERT().

  @param[in]  Port  The I/O port to read.

  @return The value read.

**/
UINT32
UnalignedIoRead32 (
  IN      UINTN                     Port
  )
{
  UINT32                            Value;

  _ReadWriteBarrier ();
  Value = _inpd ((UINT16)Port);
  _ReadWriteBarrier ();
  return Value;
}