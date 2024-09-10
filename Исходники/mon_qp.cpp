int EndJob(PORTHANDLE hPort)
{
  PSPCB pSPCB;

  TRACE0(TEXT("--EndJob\r\n"));

  if (!ValidHandle(hPort))
  {
    return(QP_BAD_PARAMETER);
  }

  pSPCB = &SPCBTable[hPort];

  pSPCB->DeviceState.bJobPresent = FALSE;
  pSPCB->DeviceState.bManualPaused = FALSE;

  // close the port
  if (ClosePort(PORT_OWN_QP,pSPCB))
  {
    TRACE0(TEXT("--ClosePort failed\r\n"));
    return(QP_FAIL);
  }

  return(QP_SUCCESS);
}