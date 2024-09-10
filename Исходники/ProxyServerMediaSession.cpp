ProxyRTSPClient::ProxyRTSPClient(ProxyServerMediaSession& ourServerMediaSession, char const* rtspURL,
				 char const* username, char const* password,
				 portNumBits tunnelOverHTTPPortNum, int verbosityLevel, int socketNumToServer)
  : RTSPClient(ourServerMediaSession.envir(), rtspURL, verbosityLevel, "ProxyRTSPClient",
	       tunnelOverHTTPPortNum == (portNumBits)(~0) ? 0 : tunnelOverHTTPPortNum, socketNumToServer),
    fOurServerMediaSession(ourServerMediaSession), fOurURL(strDup(rtspURL)), fStreamRTPOverTCP(tunnelOverHTTPPortNum != 0),
    fSetupQueueHead(NULL), fSetupQueueTail(NULL), fNumSetupsDone(0), fNextDESCRIBEDelay(1),
    fServerSupportsGetParameter(False), fLastCommandWasPLAY(False), fResetOnNextLivenessTest(False),
    fLivenessCommandTask(NULL), fDESCRIBECommandTask(NULL), fSubsessionTimerTask(NULL) { 
  if (username != NULL && password != NULL) {
    fOurAuthenticator = new Authenticator(username, password);
  } else {
    fOurAuthenticator = NULL;
  }
}