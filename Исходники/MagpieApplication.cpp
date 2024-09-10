//----------------------------------------------------------------------------
//  RunModule
HRESULT CMagpieApplication::RunModule(
  CMagpieModule           *   pSrcModule,
  LPCOLESTR                   lpszModuleID,
  CMagpieModuleComObject  **  ppRet)
{
  ATLTRACE(_T("CMagpieApplication::RunModule %s\n"), lpszModuleID);
  // load the module
  CComPtr<CMagpieModuleComObject> module;
  IF_FAILED_RET(LoadModule(pSrcModule, lpszModuleID, NULL, 9 == m_ScriptEngine.mJscriptVersion, module.p));

  if (ppRet)
  {
    module.CopyTo(ppRet);
  }

  // and run
  return module->Run();
}