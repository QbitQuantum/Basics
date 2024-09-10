zend_object_iterator *php_com_iter_get(zend_class_entry *ce, zval *object, int by_ref)
{
	php_com_dotnet_object *obj;
	struct php_com_iterator *I;
	IEnumVARIANT *iev = NULL;
	DISPPARAMS dp;
	VARIANT v;
	unsigned long n_fetched;
	zval ptr;

	if (by_ref) {
		zend_throw_error(NULL, "An iterator cannot be used with foreach by reference");
		return NULL;
	}

	obj = CDNO_FETCH(object);

	if (V_VT(&obj->v) != VT_DISPATCH && !V_ISARRAY(&obj->v)) {
		php_error_docref(NULL, E_WARNING, "variant is not an object or array VT=%d", V_VT(&obj->v));
		return NULL;
	}

	memset(&dp, 0, sizeof(dp));
	VariantInit(&v);

	I = (struct php_com_iterator*)ecalloc(1, sizeof(*I));
	zend_iterator_init(&I->iter);
	I->iter.funcs = &com_iter_funcs;
	Z_PTR(I->iter.data) = I;
	I->code_page = obj->code_page;
	ZVAL_UNDEF(&I->zdata);
	VariantInit(&I->safe_array);
	VariantInit(&I->v);

	if (V_ISARRAY(&obj->v)) {
		LONG bound;
		UINT dims;

		dims = SafeArrayGetDim(V_ARRAY(&obj->v));

		if (dims != 1) {
			php_error_docref(NULL, E_WARNING,
				   "Can only handle single dimension variant arrays (this array has %d)", dims);
			goto fail;
		}

		/* same semantics as foreach on a PHP array;
		 * make a copy and enumerate that copy */
		VariantCopy(&I->safe_array, &obj->v);

		/* determine the key value for the array */
		SafeArrayGetLBound(V_ARRAY(&I->safe_array), 1, &bound);
		SafeArrayGetUBound(V_ARRAY(&I->safe_array), 1, &I->sa_max);

		/* pre-fetch the element */
		if (php_com_safearray_get_elem(&I->safe_array, &I->v, bound)) {
			I->key = bound;
			ZVAL_NULL(&ptr);
			php_com_zval_from_variant(&ptr, &I->v, I->code_page);
			ZVAL_COPY_VALUE(&I->zdata, &ptr);
		} else {
			I->key = (ulong)-1;
		}

	} else {
		/* can we enumerate it? */
		if (FAILED(IDispatch_Invoke(V_DISPATCH(&obj->v), DISPID_NEWENUM,
						&IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD|DISPATCH_PROPERTYGET,
						&dp, &v, NULL, NULL))) {
			goto fail;
		}

		/* get something useful out of it */
		if (V_VT(&v) == VT_UNKNOWN) {
			IUnknown_QueryInterface(V_UNKNOWN(&v), &IID_IEnumVARIANT, (void**)&iev);
		} else if (V_VT(&v) == VT_DISPATCH) {
			IDispatch_QueryInterface(V_DISPATCH(&v), &IID_IEnumVARIANT, (void**)&iev);
		}

		VariantClear(&v);

		if (iev == NULL) {
			goto fail;
		}

		I->ev = iev;

		/* Get the first element now */
		if (SUCCEEDED(IEnumVARIANT_Next(I->ev, 1, &I->v, &n_fetched)) && n_fetched > 0) {
			/* indicate that we have element 0 */
			I->key = 0;
			ZVAL_NULL(&ptr);
			php_com_zval_from_variant(&ptr, &I->v, I->code_page);
			ZVAL_COPY_VALUE(&I->zdata, &ptr);
		} else {
			/* indicate that there are no more items */
			I->key = (ulong)-1;
		}
	}

	return &I->iter;

fail:
	if (I) {
		VariantClear(&I->safe_array);
		VariantClear(&I->v);
		efree(I);
	}
	return NULL;
}