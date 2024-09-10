/* sqAuthContinue: Submit a token to the authentication session.
   Arguments:
     handle - the authentication session handle
     token - the pointer to the token data
     tokensize - the length of the token data.
   Returns:
     An integer status code.
     <0 - Error. The error code is platform specific.
      0 - OK. The session is authenticated.
      1 - Another server-roundtrip is needed.
*/
int sqAuthContinue(int handle, char *token, int tokensize) {
  sqAuthData *auth = (sqAuthData*)handle;
  SECURITY_STATUS ret;
  ULONG flags = DEFAULT_AUTH_FLAGS;
  ULONG attrs = 0;

  if(auth == NULL) return -1;

  auth->inbuf[0].BufferType = SECBUFFER_TOKEN;
  auth->inbuf[0].cbBuffer = tokensize;
  auth->inbuf[0].pvBuffer = token;
  auth->inbuf[1].BufferType = SECBUFFER_EMPTY;
  auth->inbuf[1].cbBuffer = 0;
  auth->inbuf[1].pvBuffer = NULL;
  auth->sbdIn.cBuffers = 2;

  ret = InitializeSecurityContext(&auth->cred,
				  &auth->ctxt,
				  auth->principal,
				  flags, 
				  0,
				  SECURITY_NETWORK_DREP, 
				  &auth->sbdIn, 
				  0,
				  NULL,
				  &auth->sbdOut,
				  &attrs, 
				  NULL);


  if (FAILED(ret)) {
    if(debug) printf("InitializeSecurityContext failed: %x\n", ret);
    return -(ret & 0x7FFFFFFF);
  }

  if(debug) printf("InitializeSecurityContext returned: %x\n", ret);

  /* Complete token if needed */
  if(ret == SEC_I_COMPLETE_NEEDED || ret == SEC_I_COMPLETE_AND_CONTINUE)  {
    SECURITY_STATUS ss;
    ss = CompleteAuthToken (&auth->ctxt, &auth->sbdOut);
    if(FAILED(ss)) {
      if(debug) printf("CompleteAuthToken failed: %x\n", ss);
      return ss;
    }
   }

  if(ret == SEC_E_OK || ret == SEC_I_COMPLETE_NEEDED) {
    /* success; session is established */
    return 0;
  }

  if(ret == SEC_I_CONTINUE_NEEDED || ret == SEC_I_COMPLETE_AND_CONTINUE) {
    /* need another round trip */
    return 1;
  }
  return -ret;
}