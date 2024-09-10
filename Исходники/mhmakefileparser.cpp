void mhmakefileparser::SetExport(const string &Var, const string &Val)
{
  m_Exports.insert(Var);
#ifdef WIN32
  if (!m_pEnv)
  {
    /* Environment not created yet, so create one */
    char *pEnv=GetEnvironmentStrings();
    char *pEnd=pEnv;
    while (*pEnd)
    {
      while (*pEnd++);
    }
    size_t Len=pEnd-pEnv+1;
    m_pEnv=(char*)malloc(Len);
    memcpy(m_pEnv,pEnv,Len);
    m_EnvLen=Len;
    FreeEnvironmentStrings(pEnv);
  }
  /* First check if the variable is in the environment, if so remove it first */
  char *pEnv=m_pEnv;
  while (*pEnv)
  {
    const char *pVar=Var.c_str();
    char *pStart=pEnv;
    while (*pEnv!='=' && tolower(*pEnv)==tolower(*pVar))
    {
      pEnv++; pVar++;
    }
    if (*pEnv=='=' && !*pVar)
    {
      /* Variable found, remove it */
      while (*pEnv++);
      m_EnvLen-=pEnv-pStart;
      while (*pEnv)
      {
        while (*pEnv)
        {
          *pStart=*pEnv++;
          pStart++;
        }
        *pStart=*pEnv++;
        pStart++;
      }
      *pStart=*pEnv;
      break;
    }
    while (*pEnv++);
  }
  size_t VarLen=Var.length();
  size_t ValLen=Val.length();
  size_t Extra=VarLen+ValLen+2;
  /* Add the variable at the end */
  m_pEnv=(char*)realloc(m_pEnv,m_EnvLen+Extra);
  pEnv=m_pEnv+m_EnvLen-1;
  memcpy(pEnv,Var.c_str(),VarLen);
  pEnv+=VarLen;
  *pEnv++='=';
  memcpy(pEnv,Val.c_str(),ValLen);
  pEnv+=ValLen;
  *pEnv++='\0';
  *pEnv++='\0';
  m_EnvLen+=Extra;
#else
  if (!m_pEnv)
  {
    /* Environment not created yet, so create one */
    char **pEnv=environ;
    char **pEnd=pEnv;
    int Len=1;
    while (*pEnd)
    {
      Len++;
      pEnd++;
    }
    m_EnvLen=Len;
    m_pEnv=(char**)malloc(Len*sizeof(pEnv));
    int i=0;
    while (*pEnv)
    {
      m_pEnv[i]=strdup(*pEnv);
      i++;
      pEnv++;
    }
    m_pEnv[i]=NULL;
  }
  /* First check if the variable is in the environment, if so replace it */
  char **pEnv=m_pEnv;
  while (*pEnv)
  {
    const char *pVar=Var.c_str();
    char *pStart=*pEnv;
    char *pTmp=pStart;
    while (*pTmp!='=' && *pTmp==*pVar)
    {
      pTmp++; pVar++;
    }
    if (*pTmp=='=' && !*pVar)
    {
      free(*pEnv);
      *pEnv=strdup((Var+"="+Val).c_str());
      break;
    }
    pEnv++;
  }
  if (!*pEnv)
  {
    // Add it at the end of the list
    m_pEnv=(char**)realloc(m_pEnv,(m_EnvLen+1)*sizeof(*pEnv));
    m_pEnv[m_EnvLen-1]=strdup((Var+"="+Val).c_str());
    m_pEnv[m_EnvLen++]=NULL;
  }

#endif
}