void ProcessEnv::removeEnv(char **newenvs, Lng32 nEnvs)
{
  Lng32 i,j;
  CollHeap *stmtHeap = CmpCommon::statementHeap();
  NAList<Lng32> deleteArray(stmtHeap, 16);

#pragma warning (disable : 4018)  //warning elimination
  for (j=0; j < envs_.getSize(); j++)
#pragma warning (default : 4018)  //warning elimination
  {
    if (envs_.used(j))
    {
      for (i=0; i < nEnvs; i++)
        if (strcmp(newenvs[i], envs_[j]) ==0 )
          break;

        if ( i >= nEnvs )
        {
          // can't find it in newenvs, envs_[j] must have been deleted
          char* pTemp = strchr(envs_[j], '=');
          if (pTemp)
          {
            *(pTemp+1) = '\0';
            PUTENV(envs_[j]);
            NADELETEBASIC(envs_[j], heap_);
            deleteArray.insert(j);
          }
        }

    }
  }

#pragma warning (disable : 4018)  //warning elimination
  for (j=0; j < deleteArray.entries(); j++) {
#pragma warning (default : 4018)  //warning elimination
    envs_.remove(deleteArray[j]);
  }

} 