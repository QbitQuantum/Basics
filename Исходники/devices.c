Errors Device_tell(DeviceHandle *deviceHandle, uint64 *offset)
{
  off_t n;

  assert(deviceHandle != NULL);
  assert(deviceHandle->file != NULL);
  assert(offset != NULL);

  n = FTELL(deviceHandle->file);
  if (n == (off_t)(-1))
  {
    return ERRORX_(IO_ERROR,errno,String_cString(deviceHandle->name));
  }
// NYI
//assert(sizeof(off_t)==8);
assert(n == (off_t)deviceHandle->index);

  (*offset) = deviceHandle->index;

  return ERROR_NONE;
}