HRESULT CPigEngine::get_AccountDispenser(IPigAccountDispenser** ppDispenser)
{
  // Get the computer name of the account server
  CComBSTR bstrServer;
  RETURN_FAILED(get_AccountServer(&bstrServer));
  if (!bstrServer.Length())
  {
    // Get the computer name of the mission server
    RETURN_FAILED(get_MissionServer(&bstrServer));
  }

  // Check for '.' to indicate this computer
  if (1 == bstrServer.Length() && OLESTR('.') == bstrServer[0])
    bstrServer.Empty();

  // Create the Pig Account Dispenser on the mission server
  COSERVERINFO si  = {0, bstrServer, NULL, 0};
  MULTI_QI     mqi = {&IID_IPigAccountDispenser, NULL, S_OK};
  RETURN_FAILED(CoCreateInstanceEx(CLSID_PigAccountDispenser, NULL,
    CLSCTX_SERVER, &si, 1, &mqi));

  // Copy the interface pointer to the [out] parameter
  ZSucceeded(mqi.hr);
  *ppDispenser = (IPigAccountDispenser*)mqi.pItf;

  // Indicate success
  return S_OK;
}