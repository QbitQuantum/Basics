STDMETHODIMP CScdSolver::CreateSpModel(BSTR ProgID, IScdTaggedObject **pModel)
  {
  dllSCD_COMENTRYGET(long, pModel)
    {
    CLSID clsid;
    if (SUCCEEDED(CLSIDFromProgID(ProgID, &clsid)))
      {
      return Scd.ReturnH(::CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IScdTaggedObject, (void**)pModel));
      };
    return Scd.ReturnH(E_FAIL);
    }