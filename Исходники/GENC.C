ConfigData::ConfigData()
  {
  FILE *fp;
  set_new_handler(0);
  if ((fp=fopen("gm.cfg","rb"))!=NULL)
    {
    Cfg.Read(fp);
    fclose(fp);
    strcpy(WorkDir,WorkingDirectory);
    }
  else
    {
    for (uint i=0; i<MAXFILENAMELEN;i++)
      { WorkDir[i]=0; WorkingDirectory[i]=0; }
    }
  }