 IFACEMETHODIMP EnterFolder(IShellFolder *psf, PCUITEMID_CHILD pidl)
 {
     HRESULT hr = (_iCurTreeDepth < ARRAYSIZE(_rghTreeParentItemArray) - 1) ? S_OK : E_FAIL;
     if (SUCCEEDED(hr))
     {
         IShellItem *psi;
         hr = SHCreateItemWithParent(NULL, psf, pidl, IID_PPV_ARGS(&psi));
         if (SUCCEEDED(hr))
         {
             _rghTreeParentItemArray[_iCurTreeDepth + 1] = AddItemToTreeView(_hwndTreeView, psi, _rghTreeParentItemArray[_iCurTreeDepth]);
             hr = _rghTreeParentItemArray[_iCurTreeDepth + 1] ? S_OK : E_FAIL;
             _iCurTreeDepth++;
             psi->Release();
         }
     }
     return hr;
 }