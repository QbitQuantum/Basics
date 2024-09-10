static int tcp2com(
    const char *pPath,
    const ComParams &comParams,
    const char *pIF,
    const char *pPort,
    Protocol &protocol)
{
  SOCKET hSockListen = Socket(pIF, pPort);

  if (hSockListen == INVALID_SOCKET)
    return 2;

  if (listen(hSockListen, SOMAXCONN) == SOCKET_ERROR) {
    TraceLastError("tcp2com(): listen(\"%s\", \"%s\")", pIF, pPort);
    closesocket(hSockListen);
    return 2;
  }

  for (;;) {
    SOCKET hSock = Accept(hSockListen);

    if (hSock == INVALID_SOCKET)
      break;

    HANDLE hC0C = OpenC0C(pPath, comParams);

    if (hC0C != INVALID_HANDLE_VALUE) {
      InOut(hC0C, hSock, protocol, comParams.IgnoreDSR(), hSockListen);
      CloseHandle(hC0C);
    }

    Disconnect(hSock);
  }

  closesocket(hSockListen);

  return 2;
}