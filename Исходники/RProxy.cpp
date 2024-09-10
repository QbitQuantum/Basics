SEXP rCallStaticMethod(SEXP p) {
	
	// 1 - Get data from SEXP
	p = CDR(p); // Skip the first parameter: because function name
	char* strTypeName = readStringFromSexp(p); p = CDR(p);
	char* strMethodName = readStringFromSexp(p); p = CDR(p);
	SAFEARRAY* parameters = readParametersFromSexp(p);

	// 2 - Prepare arguments to call proxy
	SAFEARRAY* args = SafeArrayCreateVector(VT_VARIANT, 0, 3);
	long i = 0;
	
	// 2.1 - Type name
	variant_t typeName(strTypeName);
	SafeArrayPutElement(args, &i, &typeName); i++;
	
	// 2.2 - Method name
	variant_t methodName(strMethodName);
	SafeArrayPutElement(args, &i, &methodName); i++;

	// 2.3 parameters
	VARIANT* pvt = new variant_t();
	VariantInit(pvt);
	pvt->vt = VT_ARRAY | VT_I8;
	pvt->parray = parameters;
	SafeArrayPutElement(args, &i, pvt); i++;

	// 3 - Call the proxy
	CLR_OBJ result;
	char* errorMsg;
	HRESULT hr = callProxy(L"CallStaticMethod", args, &result, &errorMsg);
	
	if(FAILED(hr)) {
		Rprintf(errorMsg);
		error("Exception during netCallStatic !");
		free(errorMsg);
		return R_NilValue;
	}

	// 4 - Free memory
	SafeArrayDestroy(parameters);
	SafeArrayDestroy(args);
	//free_variant_array(pvt);
	//free(strTypeName);
	//free(strMethodName);

	return convertToSEXP(result);
}