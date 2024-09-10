bool doAuthentication(
  SOCKET aSocket,
  CredHandle* aphCred,
  SecHandle* aphContext)
{
  std::vector<BYTE> vInBuffer(c_dwMaxMessage, 0);
  std::vector<BYTE> vOutBuffer(c_dwMaxMessage, 0);
  DWORD dwIn = 0;
  DWORD dwOut = c_dwMaxMessage;

  bool fDone = false;
  bool fResult = genClientContext(
    NULL,
    0,
    &vOutBuffer[0],
    &dwOut,
    &fDone,
    "192.168.2.40",
    aphCred,
    aphContext);
  if(!fResult)
  {
    std::cout << "error in first genClientContext\n";
    return false;
  }

  if(!SendMsg(aSocket, &vOutBuffer[0], dwOut))
  {
    std::cout << "cannot send message = " << 
      ::GetLastError() << '\n';
    return false;
  }

  while(!fDone)
  {
    if(!ReceiveMsg(aSocket, &vInBuffer[0], c_dwMaxMessage, &dwIn))
    {
      std::cout << "cannot receive message = " << 
        ::GetLastError() << '\n';
      return false;
    }

    dwOut = c_dwMaxMessage;
    fResult = genClientContext(
      &vInBuffer[0],
      dwIn,
      &vOutBuffer[0],
      &dwOut,
      &fDone,
      "192.168.2.40",
      aphCred,
      aphContext);
    if(!fResult)
    {
      std::cout << "error in genClientContext\n";
      return false;
    }

    if(!SendMsg(aSocket, &vOutBuffer[0], dwOut))
    {
      std::cout << "cannot send message in cycle = " << 
        ::GetLastError() << '\n';
      return false;
    }
  }

  return true;
}