HRESULT CTCPropBagOnRegKey::_ReadVariant(CRegKey& key,
  const _bstr_t& strValueName, VARIANT* pVar, IErrorLog* pErrorLog)
{
  // Create an empty CComVariant object
  CComVariant v;

  // Read the specified property from the registry
  DWORD nType = 0;
  int cbData = 0;
  if (key.QueryValue(strValueName, nType, cbData))  // Name is a value?
  {
    // Read property in registry value as a VARIANT
    HRESULT hr = _ReadVariantFromValue(key, strValueName, nType, cbData, v,
      pErrorLog);
    if (FAILED(hr))
      return hr;
  }
  else if (key.Exists(strValueName))                // Name is a subkey?
  {
    // Read property on subkey as specified by subkey's VariantType value
    HRESULT hr = E_FAIL;
    if (IsSubkeySafeArray(key, strValueName))
      hr = ReadSafeArray(key, strValueName, pVar, pErrorLog);
    else if (IsSubkeyObject(key, strValueName))
    {
      // Read property on subkey as an object
      CComObjectStack<CTCPropBagOnRegKey> bag;
      bag.Init(key, _bstr_t(), this);
      V_VT(&v) = VT_UNKNOWN;
      hr = bag._CreateObject(strValueName, &V_UNKNOWN(&v), pErrorLog);
    }
    if (FAILED(hr))
      return hr;
  }
  else
  {
    // Specified name does not exist
    TRACE1("CTCPropBagOnRegKey::_ReadVariant: Property \"%s\" does not exist\n",
      strValueName);
    return E_INVALIDARG;
  }

  // Coerce the value to the specified variant type
  switch (V_VT(pVar))
  {
    // Leave value as-is if no VARIANT type was specified
    case VT_EMPTY:
      VariantCopy(pVar, v);
      break;

    // Coerce supported VARIANT types
    case VT_BOOL:
    case VT_I1:
    case VT_I2:
    case VT_I4:
    case VT_UI1:
    case VT_UI2:
    case VT_UI4:
    case VT_ERROR:
    case VT_R4:
    case VT_R8:
    case VT_DECIMAL:
    case VT_CY:
    case VT_DATE:
    case VT_BSTR:
    case VT_UNKNOWN:
    case VT_DISPATCH:
    case VT_ARRAY | VT_BOOL:
    case VT_ARRAY | VT_I1:
    case VT_ARRAY | VT_I2:
    case VT_ARRAY | VT_I4:
    case VT_ARRAY | VT_UI1:
    case VT_ARRAY | VT_UI2:
    case VT_ARRAY | VT_UI4:
    case VT_ARRAY | VT_ERROR:
    case VT_ARRAY | VT_R4:
    case VT_ARRAY | VT_R8:
    case VT_ARRAY | VT_DECIMAL:
    case VT_ARRAY | VT_CY:
    case VT_ARRAY | VT_DATE:
    case VT_ARRAY | VT_BSTR:
    case VT_ARRAY | VT_UNKNOWN:
    case VT_ARRAY | VT_DISPATCH:
    case VT_ARRAY | VT_VARIANT:
    {
      // Coerce the value to the specified VARIANT type
      VariantChangeTypeEx(pVar, v, GetThreadLocale(), m_wChangeTypeFlags,
        V_VT(pVar));
      break;
    }

    // All other VARIANT types are unsupported
    default:
    {
      // Use local resources
      MCLibRes res;

      // Format a description string
      _bstr_t strDesc;
      strDesc.Format(IDS_FMT_UNSUPPORTED_VT, UINT(V_VT(pVar)),
        UINT(V_VT(pVar)));

      // Log the error
      USES_CONVERSION;
      return LogError("ReadVariant", strDesc, E_FAIL, T2COLE(strValueName),
        pErrorLog);
    }
  }

  // Indicate success
  return S_OK;
}