//--------------------------------------------------------------------------------------------------
void catalogFile(const char *dir, const char *file)
{
  TString fileName = TString(dir) + slash +  + TString(file);
  //printf("Index: %d\n",fileName.Index("castor/cern.ch"));
  if (fileName.Index("castor/cern.ch") != -1)
    fileName = TString("castor:") + fileName;
  if (fileName.Index("pnfs/cmsaf.mit.edu") != -1) {
    fileName = dCacheDoor + fileName;
  }
  if (fileName.Index("mnt/hadoop/cms/store") != -1) {
    fileName.Remove(0,15);
    fileName = hadoopDoor + fileName;
  }
  
  printf("\n Opening: %s\n\n",fileName.Data());
  TFile* f       = TFile::Open(fileName.Data());

  TTree* tree = (TTree*) f->FindObjectAny("Delphes");
  if (tree) {
    printf("0000 %s %d %d\n",fileName.Data(),tree->GetEntries(),tree->GetEntries());
    return;
  }

  TTree* tree    = (TTree*) f->FindObjectAny("Events");
  if (tree)
    printf("XX-CATALOG-XX %s %d\n",fileName.Data(),tree->GetEntries());

  TTree* allTree = (TTree*) f->FindObjectAny("AllEvents");
  if (tree && allTree)
    printf("XX-CATALOG-XX %s %d %d\n",fileName.Data(),tree->GetEntries(),allTree->GetEntries());
}