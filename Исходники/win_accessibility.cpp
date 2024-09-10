HRESULT AccessibleObject::BuildChildren(std::vector<AccessibleChild>& children,
                                        IAccessible* acc, LPARAM param) {
  if (acc == nullptr)
    acc = acc_;
  if (acc == nullptr)
    return E_INVALIDARG;

  long child_count = 0;
  HRESULT hr = acc->get_accChildCount(&child_count);

  if (FAILED(hr))
    return hr;
  if (child_count == 0)
    return S_FALSE;

  long obtained_count = 0;
  std::vector<VARIANT> var_array(child_count);
  hr = AccessibleChildren(acc, 0L, child_count, var_array.data(),
                          &obtained_count);

  if (FAILED(hr))
    return hr;

  children.resize(obtained_count);
  for (int i = 0; i < obtained_count; i++) {
    VARIANT var_child = var_array[i];

    if (var_child.vt == VT_DISPATCH) {
      IDispatch* dispatch = var_child.pdispVal;
      IAccessible* child = nullptr;
      hr = dispatch->QueryInterface(IID_IAccessible, (void**)&child);
      if (hr == S_OK) {
        GetName(children.at(i).name, CHILDID_SELF, child);
        GetRole(children.at(i).role, CHILDID_SELF, child);
        GetValue(children.at(i).value, CHILDID_SELF, child);
        if (AllowChildTraverse(children.at(i), param))
          BuildChildren(children.at(i).children, child, param);
        child->Release();
      }
      dispatch->Release();

    } else {
      GetName(children.at(i).name, var_child.lVal, acc);
      GetRole(children.at(i).role, var_child.lVal, acc);
      GetValue(children.at(i).value, var_child.lVal, acc);
    }
  }

  return S_OK;
}