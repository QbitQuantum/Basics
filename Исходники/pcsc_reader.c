BOOL PCSC_IccTransmit (MRTD_CTX_ST * ctx, const BYTE send[], WORD send_sz, BYTE recv[], WORD * recv_sz)
{
  LONG rc;
  DWORD recv_sz_dw = 0;
  const SCARD_IO_REQUEST *pioSendPci = NULL;

  if (ctx == NULL)
    return FALSE;

  if (recv_sz != NULL)
    recv_sz_dw = *recv_sz;

  if (ctx->reader.pcsc.protocol == SCARD_PROTOCOL_T0)
  {
    pioSendPci = SCARD_PCI_T0;
  } else
  if (ctx->reader.pcsc.protocol == SCARD_PROTOCOL_T1)
  {
    pioSendPci = SCARD_PCI_T1;
  }

  rc = SCardTransmit (ctx->reader.pcsc.hcard, pioSendPci, send, send_sz, NULL, recv, &recv_sz_dw);
  if (recv_sz != NULL)
    *recv_sz = (WORD) recv_sz_dw;

  if (rc != SCARD_S_SUCCESS)
  {
    MrtdVerbose("SCardTransmit : PC/SC error %08lX", rc);
    MrtdSetLastError (ctx, MRTD_E_CARD_LOST);
    return FALSE;
  }

  return TRUE;
}