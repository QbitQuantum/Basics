BOOL TestDesfire(SCARDCONTEXT hContext, const char *szReader)
{
  SCARDHANDLE hCard;
  DWORD dwProtocol;
  LONG rc;
  BOOL f;

  printf("Testing the Desfire library on this card...\n");

  /*
   * Connect to the card, accept either T=0 or T=1
   * ---------------------------------------------
   */
  rc = SCardConnect(hContext,
                    szReader,
                    SCARD_SHARE_SHARED,
                    SCARD_PROTOCOL_T0|SCARD_PROTOCOL_T1,
                    &hCard,
                    &dwProtocol);
	if (rc != SCARD_S_SUCCESS)
  {
    printf("\tSCardConnect error %08lX\n",rc);
		return FALSE;
  }

  printf("\tConnected to the card, protocol ");
  switch (dwProtocol)
  {
    case SCARD_PROTOCOL_T0 : printf("T=0"); break;
    case SCARD_PROTOCOL_T1 : printf("T=1"); break;
    default                : printf("%08lX", dwProtocol);
  }
  printf("\n");

  
  SCardDesfire_AttachLibrary(hCard);
  f = TestDesfire_Ex(hCard);
  SCardDesfire_DetachLibrary(hCard);

  SCardDisconnect(hCard, SCARD_EJECT_CARD);


  printf("\n\n\n");
  return f;
}