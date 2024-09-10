/* -------------------------------------------------------------------------- */
LONG sc_init (sc_context *ctx, char *rdr)
{
  SCARD_READERSTATE rSt = {0};
  LONG rc=SCARD_S_SUCCESS;
  LPTSTR c=NULL, cc=NULL;
  DWORD dw=SCARD_AUTOALLOCATE;

  rc=SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &ctx->hCtx);
  if (rc==SCARD_S_SUCCESS)
  {
     rc=SCardListReaders(ctx->hCtx, NULL, (LPTSTR) &c, &dw);
     if (rc==SCARD_S_SUCCESS)
     {
        cc=findfirststr(c, rdr);
        if (cc!=NULL)
        {
           rSt.szReader = cc;
           rSt.dwCurrentState = SCARD_STATE_UNAWARE;
           rc = SCardGetStatusChange(ctx->hCtx, 0, &rSt, 1);
           if ( (rSt.dwEventState & SCARD_STATE_EMPTY) > 0 ) rc = SC_BAD;
           else
           {
               ctx->rdr = NULL;
               ctx->rdrsz = SCARD_AUTOALLOCATE;
               ctx->CLA = 0;
               ctx->proto = SCARD_PCI_T0;
               ctx->rw = 0;
               rc=SCardConnect(ctx->hCtx, cc, SCARD_SHARE_SHARED,
                               SCARD_MYPROTOSET, &ctx->hCard, &dw);
               if (dw==SCARD_PROTOCOL_T1) ctx->proto=SCARD_PCI_T1;
               else if (dw==SCARD_PROTOCOL_RAW) ctx->proto=SCARD_PCI_RAW;
               if (rc==SCARD_S_SUCCESS)
                  SCardGetAttrib(ctx->hCard, SCARD_ATTR_DEVICE_FRIENDLY_NAME,
                             (LPBYTE)&ctx->rdr, &ctx->rdrsz);
           }
        } else rc=SC_BAD;
        SCardFreeMemory(ctx->hCtx, c);
     }
     if ( rc != SCARD_S_SUCCESS) SCardReleaseContext(ctx->hCtx);
  }

  return rc;
} /* sc_init */