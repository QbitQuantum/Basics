/**
  Get a UINT16 value from buffer.

  @param[in] Buf              Pointer to input buffer.

  @return                     The UINT16 value obtained from the buffer.

**/
UINT16
TcpGetUint16 (
  IN UINT8 *Buf
  )
{
  UINT16  Value;
  CopyMem (&Value, Buf, sizeof (UINT16));
  return NTOHS (Value);
}