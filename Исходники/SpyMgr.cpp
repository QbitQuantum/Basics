HRESULT CNktSpyMgrImpl::TerminateProcess(__in VARIANT procOrId, __in LONG exitCode)
{
  TNktComPtr<CNktDvProcess> cProc;
  DWORD dwPid;
  HRESULT hRes;

  get_InterfaceError(&hRes);
  if (FAILED(hRes))
    return SetupErrorInfoAndReturn(E_FAIL);
  if (nInitialized == 0)
    return SetupErrorInfoAndReturn(E_ACCESSDENIED);
  //check procOrId param
  hRes = ProcId_From_Variant(&cProc, &dwPid, RealVariant_From_Variant(&procOrId));
  if (SUCCEEDED(hRes))
  {
    //call terminate process
    if (dwPid != 0)
      hRes = CNktDvProcess::Terminate(dwPid, (DWORD)exitCode);
    else
      cProc->Terminate((DWORD)exitCode);
  }
  return SetupErrorInfoAndReturn(hRes);
}