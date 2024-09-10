void ModuleLoader::setModuleDirectory(const char* directory)
{
  DIR* dir;
  struct dirent* ent;
  const size_t len = strlen(directory) + 256 + 1;
  char* fname;
  IServiceManager* servmgr;

  dir = opendir(directory);
  if(!dir)
    return;

  fname = static_cast<char*>(malloc(len));
  servmgr = XPLC_getServiceManager();

  rewinddir(dir);
  while((ent = readdir(dir)) && fname && servmgr) {
    snprintf(fname, len, "%s/%s", directory, ent->d_name);

    loadModule(fname);
  }

  if(servmgr)
    servmgr->release();

  free(fname);

  closedir(dir);
}