/******************************************************************************
 * This method is part of the ILockBytes interface.
 *
 * It will change the size of the byte array.
 *
 * See the documentation of ILockBytes for more info.
 */
static HRESULT WINAPI HGLOBALLockBytesImpl_SetSize(
      ILockBytes*     iface,
      ULARGE_INTEGER  libNewSize)   /* [in] */
{
  HGLOBALLockBytesImpl* const This=(HGLOBALLockBytesImpl*)iface;
  HGLOBAL supportHandle;

  /*
   * As documented.
   */
  if (libNewSize.u.HighPart != 0)
    return STG_E_INVALIDFUNCTION;

  if (This->byteArraySize.u.LowPart == libNewSize.u.LowPart)
    return S_OK;

  /*
   * Re allocate the HGlobal to fit the new size of the stream.
   */
  supportHandle = GlobalReAlloc(This->supportHandle, libNewSize.u.LowPart, 0);

  if (supportHandle == 0)
    return STG_E_MEDIUMFULL;

  This->supportHandle = supportHandle;
  This->byteArraySize.u.LowPart = libNewSize.u.LowPart;

  return S_OK;
}