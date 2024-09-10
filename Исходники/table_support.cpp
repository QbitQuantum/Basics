void walk_tree(IAccessible *pAccessible, char **pColumnHeaderNames, long *pColumnHeadersCount) {
	HRESULT hr ;
	long childCount ;

	hr = pAccessible->get_accChildCount(&childCount) ;
	if (FAILED(hr) || childCount == 0)
		return ;

	VARIANT *pChildVariants = new VARIANT[childCount] ;
	long childrenFound ;
	hr = AccessibleChildren(pAccessible, 0, childCount, pChildVariants, &childrenFound) ;
	if (FAILED(hr))
		return ;

	for (int i=1; i < childrenFound + 1; i++) {
		VARIANT vChild = pChildVariants[i] ;
		if (vChild.vt == VT_DISPATCH) {
			IDispatch *pDispatch = vChild.pdispVal ;
			IAccessible *pChildAccessible = NULL ;
			hr = pDispatch->QueryInterface(IID_IAccessible, (void**) &pChildAccessible) ;
			if (hr == S_OK) {
				walk_tree(pChildAccessible, pColumnHeaderNames, pColumnHeadersCount) ;

				pChildAccessible->Release() ;
			}

			pDispatch->Release() ;
		} else {
			long role ;
			get_role(i, pAccessible, &role) ;
			if (role == 0x19) {
				if (pColumnHeaderNames == NULL) {
					*pColumnHeadersCount = *pColumnHeadersCount + 1 ;
				} else {
					char *headerName = (char *)malloc(sizeof(char) * BUFFER_SIZE) ;
					get_name(i, pAccessible, headerName) ;
					pColumnHeaderNames[i - 1] = headerName ;
				}
			}
		}
	}
}