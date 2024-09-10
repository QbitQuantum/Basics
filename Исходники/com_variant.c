static void variant_unary_operation(enum variant_unary_opcode op, INTERNAL_FUNCTION_PARAMETERS) /* {{{ */
{
	VARIANT vres;
	VARIANT left_val;
	VARIANT *vleft = NULL;
	zval *zleft = NULL;
	php_com_dotnet_object *obj;
	HRESULT result;
	int codepage = CP_ACP;

	VariantInit(&left_val);
	VariantInit(&vres);

	if (SUCCESS == zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET,
			ZEND_NUM_ARGS(), "O", &zleft, php_com_variant_class_entry)) {
		obj = CDNO_FETCH(zleft);
		vleft = &obj->v;
	} else if (SUCCESS == zend_parse_parameters(ZEND_NUM_ARGS(),
			"z!", &zleft)) {
		vleft = &left_val;
		php_com_variant_from_zval(vleft, zleft, codepage);
	} else {
		return;
	}

	switch (op) {
		case VOP_ABS:
			result = VarAbs(vleft, &vres);
			break;
		case VOP_FIX:
			result = VarFix(vleft, &vres);
			break;
		case VOP_INT:
			result = VarInt(vleft, &vres);
			break;
		case VOP_NEG:
			result = VarNeg(vleft, &vres);
			break;
		case VOP_NOT:
			result = VarNot(vleft, &vres);
			break;
		default:
			result = E_INVALIDARG;
	}

	if (SUCCEEDED(result)) {
		php_com_wrap_variant(return_value, &vres, codepage);
	} else {
		php_com_throw_exception(result, NULL);
	}

	VariantClear(&vres);
	VariantClear(&left_val);
}