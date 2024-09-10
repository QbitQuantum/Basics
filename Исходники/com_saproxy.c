static zval *saproxy_read_dimension(zend_object *object, zval *offset, int type, zval *rv)
{
	php_com_saproxy *proxy = (php_com_saproxy*) object;
	UINT dims, i;
	SAFEARRAY *sa;
	LONG ubound, lbound;
	HRESULT res;

	ZVAL_NULL(rv);

	if (V_VT(&proxy->obj->v) == VT_DISPATCH) {
		VARIANT v;
		zval *args;

		/* prop-get using first dimension as the property name,
		 * all subsequent dimensions and the offset as parameters */

		args = safe_emalloc(proxy->dimensions + 1, sizeof(zval), 0);

		for (i = 1; i < (UINT) proxy->dimensions; i++) {
			args[i-1] = proxy->indices[i];
		}
		ZVAL_COPY_VALUE(&args[i-1], offset);

		convert_to_string(&proxy->indices[0]);
		VariantInit(&v);

		res = php_com_do_invoke(proxy->obj, Z_STRVAL(proxy->indices[0]),
			   	Z_STRLEN(proxy->indices[0]), DISPATCH_METHOD|DISPATCH_PROPERTYGET, &v,
			   	proxy->dimensions, args, 0);

		if (res == SUCCESS) {
			php_com_zval_from_variant(rv, &v, proxy->obj->code_page);
			VariantClear(&v);
		} else if (res == DISP_E_BADPARAMCOUNT) {
			/* return another proxy */
			php_com_saproxy_create(object, rv, offset);
		}

		return rv;

	} else if (!V_ISARRAY(&proxy->obj->v)) {
		php_com_throw_exception(E_INVALIDARG, "invalid read from com proxy object");
		return rv;
	}

	/* the SafeArray case */

	/* offset/index must be an integer */
	convert_to_long(offset);

	sa = V_ARRAY(&proxy->obj->v);
	dims = SafeArrayGetDim(sa);

	if ((UINT) proxy->dimensions >= dims) {
		/* too many dimensions */
		php_com_throw_exception(E_INVALIDARG, "too many dimensions!");
		return rv;
	}

	/* bounds check */
	SafeArrayGetLBound(sa, proxy->dimensions, &lbound);
	SafeArrayGetUBound(sa, proxy->dimensions, &ubound);

	if (Z_LVAL_P(offset) < lbound || Z_LVAL_P(offset) > ubound) {
		php_com_throw_exception(DISP_E_BADINDEX, "index out of bounds");
		return rv;
	}

	if (dims - 1 == proxy->dimensions) {
		LONG *indices;
		VARTYPE vt;
		VARIANT v;

		VariantInit(&v);

		/* we can return a real value */
		indices = safe_emalloc(dims, sizeof(LONG), 0);

		/* copy indices from proxy */
		for (i = 0; i < dims; i++) {
			convert_to_long(&proxy->indices[i]);
			indices[i] = (LONG)Z_LVAL(proxy->indices[i]);
		}

		/* add user-supplied index */
		indices[dims-1] = (LONG)Z_LVAL_P(offset);

		/* now fetch the value */
		if (FAILED(SafeArrayGetVartype(sa, &vt)) || vt == VT_EMPTY) {
			vt = V_VT(&proxy->obj->v) & ~VT_ARRAY;
		}

		if (vt == VT_VARIANT) {
			res = SafeArrayGetElement(sa, indices, &v);
		} else {
			V_VT(&v) = vt;
			res = SafeArrayGetElement(sa, indices, &v.lVal);
		}

		efree(indices);

		if (SUCCEEDED(res)) {
			php_com_wrap_variant(rv, &v, proxy->obj->code_page);
		} else {
			php_com_throw_exception(res, NULL);
		}

		VariantClear(&v);

	} else {
		/* return another proxy */
		php_com_saproxy_create(object, rv, offset);
	}

	return rv;
}