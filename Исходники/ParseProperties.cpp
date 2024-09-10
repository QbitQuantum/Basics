HRESULT ParseMtProp(const UString &name, const PROPVARIANT &prop, UInt32 defaultNumThreads, UInt32 &numThreads)
{
  if (name.IsEmpty())
  {
    switch(prop.vt)
    {
      case VT_UI4:
        numThreads = prop.ulVal;
        break;
      default:
      {
        bool val;
        RINOK(SetBoolProperty(val, prop));
        numThreads = (val ? defaultNumThreads : 1);
        break;
      }
    }
  }
  else
  {
    UInt32 number;
    int index = ParseStringToUInt32(name, number);
    if (index != name.Length())
      return E_INVALIDARG;
    numThreads = number;
  }
  return S_OK;
}