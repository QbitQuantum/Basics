static HRESULT WINAPI NoStatStreamImpl_CopyTo(
				    IStream*      iface,
				    IStream*      pstm,         /* [unique][in] */
				    ULARGE_INTEGER  cb,           /* [in] */
				    ULARGE_INTEGER* pcbRead,      /* [out] */
				    ULARGE_INTEGER* pcbWritten)   /* [out] */
{
  HRESULT        hr = S_OK;
  BYTE           tmpBuffer[128];
  ULONG          bytesRead, bytesWritten, copySize;
  ULARGE_INTEGER totalBytesRead;
  ULARGE_INTEGER totalBytesWritten;

  if ( pstm == 0 )
    return STG_E_INVALIDPOINTER;
  totalBytesRead.u.LowPart = totalBytesRead.u.HighPart = 0;
  totalBytesWritten.u.LowPart = totalBytesWritten.u.HighPart = 0;

  while ( cb.u.LowPart > 0 )
  {
    if ( cb.u.LowPart >= 128 )
      copySize = 128;
    else
      copySize = cb.u.LowPart;
    IStream_Read(iface, tmpBuffer, copySize, &bytesRead);
    totalBytesRead.u.LowPart += bytesRead;
    IStream_Write(pstm, tmpBuffer, bytesRead, &bytesWritten);
    totalBytesWritten.u.LowPart += bytesWritten;
    if (bytesRead != bytesWritten)
    {
      hr = STG_E_MEDIUMFULL;
      break;
    }
    if (bytesRead!=copySize)
      cb.u.LowPart = 0;
    else
      cb.u.LowPart -= bytesRead;
  }
  if (pcbRead)
  {
    pcbRead->u.LowPart = totalBytesRead.u.LowPart;
    pcbRead->u.HighPart = totalBytesRead.u.HighPart;
  }

  if (pcbWritten)
  {
    pcbWritten->u.LowPart = totalBytesWritten.u.LowPart;
    pcbWritten->u.HighPart = totalBytesWritten.u.HighPart;
  }
  return hr;
}