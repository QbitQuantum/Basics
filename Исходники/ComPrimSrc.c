HRESULT primGetActiveObject( CLSID* clsid, IUnknown** unk )
{
  if (!unk) return E_POINTER;
       else *unk = NULL;
  return GetActiveObject( clsid, NULL, unk );
}