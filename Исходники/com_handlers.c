static union _zend_function *com_method_get(zend_object **object_ptr, zend_string *name, const zval *key)
{
	zend_internal_function f, *fptr = NULL;
	union _zend_function *func;
	DISPID dummy;
	php_com_dotnet_object *obj = (php_com_dotnet_object*)*object_ptr;

	if (V_VT(&obj->v) != VT_DISPATCH) {
		return NULL;
	}

	if (FAILED(php_com_get_id_of_name(obj, name->val, name->len, &dummy))) {
		return NULL;
	}

	/* check cache */
	if (obj->method_cache == NULL || NULL == (fptr = zend_hash_find_ptr(obj->method_cache, name))) {
		f.type = ZEND_OVERLOADED_FUNCTION;
		f.num_args = 0;
		f.arg_info = NULL;
		f.scope = obj->ce;
		f.fn_flags = ZEND_ACC_CALL_VIA_HANDLER;
		f.function_name = zend_string_copy(name);
		f.handler = PHP_FN(com_method_handler);

		fptr = &f;

		if (obj->typeinfo) {
			/* look for byref params */
			ITypeComp *comp;
			ITypeInfo *TI = NULL;
			DESCKIND kind;
			BINDPTR bindptr;
			OLECHAR *olename;
			ULONG lhash;
			int i;

			if (SUCCEEDED(ITypeInfo_GetTypeComp(obj->typeinfo, &comp))) {
				olename = php_com_string_to_olestring(name->val, name->len, obj->code_page);
				lhash = LHashValOfNameSys(SYS_WIN32, LOCALE_SYSTEM_DEFAULT, olename);

				if (SUCCEEDED(ITypeComp_Bind(comp, olename, lhash, INVOKE_FUNC, &TI, &kind, &bindptr))) {
					switch (kind) {
						case DESCKIND_FUNCDESC:
							f.arg_info = ecalloc(bindptr.lpfuncdesc->cParams, sizeof(zend_arg_info));

							for (i = 0; i < bindptr.lpfuncdesc->cParams; i++) {
								f.arg_info[i].allow_null = 1;
								if (bindptr.lpfuncdesc->lprgelemdescParam[i].paramdesc.wParamFlags & PARAMFLAG_FOUT) {
									f.arg_info[i].pass_by_reference = ZEND_SEND_BY_REF;
								}
							}

							f.num_args = bindptr.lpfuncdesc->cParams;

							ITypeInfo_ReleaseFuncDesc(TI, bindptr.lpfuncdesc);
							break;

							/* these should not happen, but *might* happen if the user
							 * screws up; lets avoid a leak in that case */
						case DESCKIND_VARDESC:
							ITypeInfo_ReleaseVarDesc(TI, bindptr.lpvardesc);
							break;
						case DESCKIND_TYPECOMP:
							ITypeComp_Release(bindptr.lptcomp);
							break;

						case DESCKIND_NONE:
							break;
					}
					if (TI) {
						ITypeInfo_Release(TI);
					}
				}
				ITypeComp_Release(comp);
				efree(olename);
			}
		}

		zend_set_function_arg_flags((zend_function*)&f);
		/* save this method in the cache */
		if (!obj->method_cache) {
			ALLOC_HASHTABLE(obj->method_cache);
			zend_hash_init(obj->method_cache, 2, NULL, function_dtor, 0);
		}

		zend_hash_update_mem(obj->method_cache, name, &f, sizeof(f));
	}

	if (fptr) {
		/* duplicate this into a new chunk of emalloc'd memory,
		 * since the engine will efree it */
		func = emalloc(sizeof(*fptr));
		memcpy(func, fptr, sizeof(*fptr));

		return func;
	}

	return NULL;
}