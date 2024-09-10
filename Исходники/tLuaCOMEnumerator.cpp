int tLuaCOMEnumerator::callCOMmethod(lua_State* L, const char *name, int first_param, int num_params)
{
  HRESULT hr = S_OK;

  // Next method
  if(strcmp(name, "Next") == 0)
  {
    unsigned long num_elements = 1;
    if(num_params > 0)
    {
      num_elements = (unsigned long) lua_tonumber(L, first_param);
    }

    VARIANT* pVar = new VARIANT[num_elements];

    for(unsigned long counter = 0; counter <  num_elements; counter++)
      VariantInit(&pVar[counter]);

    ULONG fetched = 0;
    hr = pEV->Next(num_elements, pVar, &fetched);
    
    for(unsigned long counter = 0; counter < fetched; counter++)
    {
      typehandler->com2lua(L, pVar[counter]);
      typehandler->releaseVariant(&pVar[counter]);
    }

    for(unsigned long counter = 0; counter <  num_elements; counter++)
      VariantClear(&pVar[counter]);

    delete[] pVar;

    pVar = NULL;

    return fetched;
  }

  if(strcmp(name, "Reset") == 0)
  {
    hr = pEV->Reset();
    CHK_LCOM_ERR(hr == S_OK, "Unable to reset enumeration.");
    
    return 0;
  }

  if(strcmp(name, "Skip") == 0)
  {
    CHK_LCOM_ERR(num_params > 0, "Not enough parameters.");

    unsigned long num_elements = (unsigned long) lua_tonumber(L, first_param);

    hr = pEV->Skip(num_elements);

    lua_pushboolean(L, hr == S_OK);
    return 1;
  }

  if(strcmp(name, "Clone") == 0)
  {
    tCOMPtr<IEnumVARIANT> p_newEV;
    CHK_COM_CODE(pEV->Clone(&p_newEV));

    tLuaCOMEnumerator* enumerator = new tLuaCOMEnumerator(p_newEV);
    
    enumerator->push(L);
    return 1;
  }

  return 0;
}