/* {{{ proto int com_load(string module_name)
   Loads a COM module */
void php3_COM_load(INTERNAL_FUNCTION_PARAMETERS)
{
	pval *module_name;
	CLSID clsid;
	HRESULT hr;
	OLECHAR *ProgID;
	IUnknown FAR *i_unknown = NULL;
	IDispatch FAR *i_dispatch = NULL;
	char *error_message;
	char *clsid_str;
	int i;

	if (ARG_COUNT(ht)!=1 || getParameters(ht, 1, &module_name)==FAILURE) {
		WRONG_PARAM_COUNT;
	}

	convert_to_string(module_name);
	ProgID = (OLECHAR *) emalloc(sizeof(OLECHAR)*(module_name->value.str.len+1));
	for (i=0; i<module_name->value.str.len; i++) {
		ProgID[i] = module_name->value.str.val[i];
	}
	ProgID[i] = 0;
	hr=CLSIDFromProgID(ProgID, &clsid);
	efree(ProgID);

	/* obtain CLSID */
	if (FAILED(hr)) {
		error_message = _php3_COM_error_message(hr);
		php3_error(E_WARNING,"Invalid ProgID:  %s\n", error_message);
		LocalFree(error_message);
		RETURN_FALSE;
	}

	/* obtain IUnknown */
	if (FAILED(hr=CoCreateInstance(&clsid, NULL, CLSCTX_ALL, &IID_IUnknown, (void FAR* FAR*) &i_unknown))) {
		error_message = _php3_COM_error_message(hr);
		clsid_str = _php3_string_from_clsid(&clsid);
		php3_error(E_WARNING,"Unable to obtain IUnknown interface for CLSID %s:  %s",clsid_str,error_message);
		LocalFree(error_message);
		efree(clsid_str);
		RETURN_FALSE;
	}

	/* obtain IDispatch */
	if (FAILED(hr=i_unknown->lpVtbl->QueryInterface(i_unknown, &IID_IDispatch, (void FAR* FAR*) &i_dispatch))) {
		error_message = _php3_COM_error_message(hr);
		clsid_str = _php3_string_from_clsid(&clsid);
		php3_error(E_WARNING,"Unable to obtain IDispatch interface for CLSID %s:  %s",clsid_str,error_message);
		LocalFree(error_message);
		efree(clsid_str);
		RETURN_FALSE;
	}
	i_unknown->lpVtbl->Release(i_unknown);

	RETURN_LONG(php3_list_insert(i_dispatch,le_idispatch));
}