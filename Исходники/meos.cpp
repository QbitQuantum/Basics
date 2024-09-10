void Setup(bool overwrite, bool overwriteAll)
{
  static bool isSetup=false;
  if (isSetup && overwrite==false)
    return;
  isSetup=true; //Run at most once.

  vector<pair<string, bool> > toInstall;
  for(int k=0;k<setup::nFiles;k++) {
    toInstall.push_back(make_pair(string(setup::fileList[k]), overwriteAll));
  }

  char dir[260];
  GetCurrentDirectory(260, dir);
  vector<string> dyn;
  expandDirectory(dir, "*.lxml", dyn);
  expandDirectory(dir, "*.listdef", dyn);
  expandDirectory(dir, "*.meos", dyn);
  for (size_t k = 0; k < dyn.size(); k++)
    toInstall.push_back(make_pair(dyn[k], true));

  char bf[260];
  for(size_t k=0; k<toInstall.size(); k++) {
    const string src = toInstall[k].first.c_str();
    char filename[128];
    char ext[32];
    _splitpath_s(src.c_str(), NULL, 0, NULL,0, filename, 128, ext, 32);
    string fullFile = string(filename) + ext;
    
    getUserFile(bf, fullFile.c_str());
    bool canOverwrite = overwrite && toInstall[k].second;
    CopyFile(toInstall[k].first.c_str(), bf, !canOverwrite);
  }
}