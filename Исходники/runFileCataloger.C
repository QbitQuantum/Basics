//--------------------------------------------------------------------------------------------------
void catalogFile(const char *dir, const char *file)
{
  // set up the modules
  gMod->SetMetaDataString((TString(dir)+slash+TString(file)).Data());
  gMod->SetNFileSet(0);

  // set up analysis
  //hMod->Add(gMod);
  //gAna->SetSuperModule(hMod);
  gAna->SetSuperModule(gMod);
  
  TString fileName = TString(dir) + slash +  + TString(file);
  //printf("Index: %d\n",fileName.Index("castor/cern.ch"));
  if (fileName.Index("castor/cern.ch") != -1)
    fileName = TString("castor:") + fileName;
  if (fileName.Index("mnt/hadoop/cms/store") != -1) {
    fileName.Remove(0,15);
    fileName = hadoopDoor + fileName;
    gMod->SetMetaDataString(fileName.Data());
  }
  
  printf(" Adding: %s\n",fileName.Data());
  gAna->AddFile(fileName);
  gAna->SetUseHLT(0);
  gAna->SetCacheSize(64*1024*1024);

  // run the analysis after successful initialisation
  gAna->Run(false);
}