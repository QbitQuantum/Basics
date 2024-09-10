bool tLuaCOM::getFUNCDESC(const char *name, FuncInfo& funcinfo)
{
  // First, tries to see we have the FUNCDESC's cached

  long counter = 0;

  for(counter = 0; counter < MAX_FUNCINFOS; counter++)
  {
    // when .name is NULL, there is no further information
    if(pFuncInfo[counter].name == NULL)
      break;

    if(strcmp(name, pFuncInfo[counter].name) == 0)
      break;
  }

  // checks whether funcinfo was found
  if(counter < MAX_FUNCINFOS && pFuncInfo[counter].name != NULL)
  {
    funcinfo = pFuncInfo[counter];
    return true;
  }

  // did not find, so gets type information through
  // ITypeComp

  HRESULT hr = S_OK;
  BINDPTR bindptr;
  DESCKIND desckind;
  BSTR wName;
  ITypeInfo *info = NULL;

  unsigned int dumb = 0;

  wName = tUtil::string2bstr(name);

  unsigned long lhashval = LHashValOfName(LOCALE_SYSTEM_DEFAULT, wName);

  hr = ptcomp->Bind(wName, lhashval, INVOKE_PROPERTYGET,
    &info, &desckind, &bindptr);
  
  if(FAILED(hr) || desckind == DESCKIND_NONE)
    funcinfo.propget = NULL;
  else
  {
    funcinfo.propget = bindptr.lpfuncdesc;
    info->Release();
  }

  hr = ptcomp->Bind(wName, lhashval, INVOKE_FUNC,
    &info, &desckind, &bindptr);
  
  if(FAILED(hr) || desckind == DESCKIND_NONE)
    funcinfo.func = NULL;
  else
  {
    funcinfo.func = bindptr.lpfuncdesc;
    info->Release();
  }


  hr = ptcomp->Bind(wName, lhashval, INVOKE_PROPERTYPUT,
    &info, &desckind, &bindptr);
  
  if(FAILED(hr) || desckind == DESCKIND_NONE)
    funcinfo.propput = NULL;
  else
  {
    funcinfo.propput = bindptr.lpfuncdesc;
    info->Release();
  }

  // if there is not propertyput, then tries propputref

  if(funcinfo.propput == NULL)
  {
    hr = ptcomp->Bind(wName, lhashval, INVOKE_PROPERTYPUTREF,
      &info, &desckind, &bindptr);

    if(FAILED(hr) || desckind == DESCKIND_NONE)
      funcinfo.propput = NULL;
    else
    {
      funcinfo.propput = bindptr.lpfuncdesc;
      info->Release();
    }
  }

  SysFreeString(wName);

  // If no type information found, returns NULL
  if(!funcinfo.propget && !funcinfo.propput && !funcinfo.func)
    return false;
  else if(counter < MAX_FUNCINFOS)
  {
    CHECKPRECOND(pFuncInfo[counter].name == NULL);

    pFuncInfo[counter].name = tUtil::strdup(name);

    pFuncInfo[counter].propget  = funcinfo.propget;
    pFuncInfo[counter].propput  = funcinfo.propput;
    pFuncInfo[counter].func     = funcinfo.func;

    return true;
  }
  else
    return true;
}