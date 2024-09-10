TInt CBtListenBase::PutCompleteIndication(void)
{
  if(iCurrObject)
  {
    TFileName newName(KObexDrive);
    newName.Append(iCurrObject->Name());
    DeleteObject();
    RFs fs;
    if(fs.Connect()==KErrNone)
    {
      if(fs.Rename(FileName(),newName)!=KErrNone) fs.Delete(FileName());
    }
  }
  return KErrNone;
}