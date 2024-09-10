CNktDvDbObjectNoRef* CNktDvExportedFunction::GetFunctionEntry() const
{
  if (nDbObjInitialized == 0)
  {
    CNktDvExportedFunction *lpThis = const_cast<CNktDvExportedFunction*>(this);
    {
      CNktAutoFastMutex cLock(&(lpThis->GetLockObject()));

      if (nDbObjInitialized == 0)
      {
        //search the DbObject in the database the first time it is required
        lpThis->lpDbObj = (cDvDB != NULL) ? (cDvDB->FindFunctionByName(GetName())) : NULL;
        NktInterlockedExchange(&(lpThis->nDbObjInitialized), 1);
      }
    }
  }
  return lpDbObj;
}