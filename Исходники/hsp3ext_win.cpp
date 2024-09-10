void *comget_variant( VARIANT *var, int *restype, BOOL fvariantret /* = FALSE*/ )
{
	//	VARIANT型→HSPの型に変換する
	//
	int size;
	BSTR bstr;
/*
	rev 43
	mingw : warning : 定数へのポインタを非定数へのポインタに代入
	に対処
*/
	void const *ptr;
	if ( fvariantret ) {
		VariantCopy( &comconv_var, var );
		*restype = HSPVAR_FLAG_VARIANT;
		return &comconv_var;
	}

	VariantCopyInd( &comconv_var, var );
	switch ( comconv_var.vt ) {

	case VT_R4:
		VariantChangeType( &comconv_var, &comconv_var, VARIANT_NOVALUEPROP, VT_R8 );
	case VT_R8:
		*restype = HSPVAR_FLAG_DOUBLE;
		return &comconv_var.dblVal;

	case VT_BSTR:
		// 文字列全体を返すため、ANSI文字列をバイナリデータBSTRとして格納
		ptr = comconv_var.bstrVal;
		if ( ptr == NULL ) ptr = L"";
		size = cnvsjis( NULL, (char *)ptr, 0 );
		bstr = SysAllocStringByteLen( NULL, size );
		if ( bstr == NULL ) throw HSPERR_OUT_OF_MEMORY;
		cnvsjis( (char *)bstr, (char *)ptr, size );
		SysFreeString( comconv_var.bstrVal );
		comconv_var.bstrVal = bstr;
		*restype = HSPVAR_FLAG_STR;
		return comconv_var.bstrVal;

	case VT_DISPATCH:
	case VT_UNKNOWN:
		*restype = HSPVAR_FLAG_COMSTRUCT;
		return &comconv_var.punkVal;

	case VT_I2:
	case VT_UI2:
	case VT_I1:
	case VT_UI1:
	case VT_I8:
	case VT_UI8:
	case VT_BOOL:
		VariantChangeType( &comconv_var, &comconv_var, VARIANT_NOVALUEPROP, VT_I4 );
	case VT_I4:
	case VT_UI4:
	case VT_ERROR:
	case VT_INT:
	case VT_UINT:
		*restype = HSPVAR_FLAG_INT;
		return &comconv_var.lVal;

	default:
		if ( comconv_var.vt & VT_ARRAY ) {
			*restype = HSPVAR_FLAG_VARIANT;		// SafeArray は Variant 型変数で扱う
			return &comconv_var;
		}
		throw HSPERR_INVALID_TYPE;
	}
}