STDMETHODIMP
tLuaCOMClassFactory::LockServer(BOOL fLock)
{    
  CoLockObjectExternal(object, fLock, TRUE); 
  return NOERROR;       
}