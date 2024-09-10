HRESULT ArcLib::get_bytes_prop(UInt32 index, PROPID prop_id, ByteVector& value) const {
  PropVariant prop;
  HRESULT res = get_prop(index, prop_id, prop.ref());
  if (res != S_OK)
    return res;
  if (prop.vt == VT_BSTR) {
    UINT len = SysStringByteLen(prop.bstrVal);
    unsigned char* data =  reinterpret_cast<unsigned char*>(prop.bstrVal);
    value.assign(data, data + len);
  }
  else
    return E_FAIL;
  return S_OK;
}