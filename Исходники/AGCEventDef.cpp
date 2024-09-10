HRESULT __fastcall
CAGCEventDef::ParseState_ProcessVar(CAGCEventDef::XParseData& data)
{
  // Get the variable as a VT_BSTR variant
  UINT cch = data.m_pszVarEnd - data.m_pszVarBegin;
  CComVariant varKey;
  V_VT(&varKey) = VT_BSTR;
  V_BSTR(&varKey) = ::SysAllocStringLen(data.m_pszVarBegin, cch);
  if (!V_BSTR(&varKey))
  {
    data.m_pfnNextState = NULL;
    return E_OUTOFMEMORY;
  }

  // Lookup the variable in the event's properties
  CComVariant varValue;
  HRESULT hr = data.m_pEvent->get_Property(&varKey, &varValue);
  if (FAILED(hr))
  {
    data.m_pfnNextState = NULL;
    return hr;
  }

  // Just write the variable name as-is if it doesn't exist in the event
  if (VT_EMPTY == V_VT(&varValue))
  {
    // Include the leading and trailing '%' characters
    --data.m_pszVarBegin;
    ++data.m_pszVarEnd;

    if (data.m_pParams)
    {
      cch = data.m_pszVarEnd - data.m_pszVarBegin;
      BSTR bstrValue = SysAllocStringLen(data.m_pszVarBegin, cch);
      if (!bstrValue)
      {
        data.m_pfnNextState = NULL;
        return E_OUTOFMEMORY;
      }
      data.m_pParams->push_back(bstrValue);
    }
    return ParseState_WriteVar(data);
  }

  // Convert the variant to a string  
  if (VT_BSTR != V_VT(&varValue))
  {
    VariantChangeTypeEx(&varValue, &varValue, GetThreadLocale(),
      VARIANT_LOCALBOOL | VARIANT_ALPHABOOL, VT_BSTR);
    if (VT_BSTR != V_VT(&varValue))
    {
      data.m_pfnNextState = ParseState_Base;
      return S_OK;
    }
  }
  UINT cchValue = BSTRLen(V_BSTR(&varValue));
  if (!cchValue)
  {
    if (data.m_pParams)
    {
      BSTR bstrValue = SysAllocString(L"");
      if (!bstrValue)
      {
        data.m_pfnNextState = NULL;
        return E_OUTOFMEMORY;
      }
      data.m_pParams->push_back(bstrValue);
    }
    data.m_pfnNextState = ParseState_Base;
    return S_OK;
  }

  // Write the value string
  data.m_pszVarBegin = V_BSTR(&varValue);
  data.m_pszVarEnd   = data.m_pszVarBegin + cchValue;
  RETURN_FAILED(ParseState_WriteVar(data));
  if (data.m_pParams)
  {
    data.m_pParams->push_back(V_BSTR(&varValue));
    V_VT(&varValue) = VT_EMPTY; // Detaches the BSTR from the VARIANT
  }

  // Indicate success
  return S_OK;
}