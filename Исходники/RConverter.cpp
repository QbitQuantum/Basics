//-----------------------------------------------------------------------------
/// Switch to object directory (=Parent directory)
TDirectory* RootHistCnv::RConverter::changeDirectory(DataObject* pObject)
//-----------------------------------------------------------------------------
{
  if ( pObject )    {
    IRegistry* pReg = pObject->registry();
    if ( pReg )    {
      SmartIF<IDataManagerSvc> dataMgr(dataProvider());
      if ( dataMgr.isValid() )    {
        IRegistry* pParentReg = 0;
        StatusCode status = dataMgr->objectParent(pReg, pParentReg);
        if ( status.isSuccess() )  {
          IOpaqueAddress* pParAddr = pParentReg->address();
          if ( pParAddr )   {
            TDirectory* pParentDir = (TDirectory*)pParAddr->ipar()[0];
            if ( pParentDir )   {
              gDirectory->cd(pParentDir->GetPath());
              return pParentDir;
            }
          }
        }
      }
    }
  }
  return 0;
}