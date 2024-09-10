SCODE CCmdTarget::SetStandardProp(const AFX_DISPMAP_ENTRY* pEntry,
	DISPPARAMS* pDispParams, UINT* puArgErr)
{
	ASSERT(pEntry != NULL);
	ASSERT(*puArgErr != 0);

	// it is a DISPATCH_PROPERTYSET (for standard, non-function property)
	SCODE sc = S_OK;
	VARIANT va;
	AfxVariantInit(&va);
	VARIANT* pArg = &pDispParams->rgvarg[0];
	if (pEntry->vt != VT_VARIANT && pArg->vt != pEntry->vt)
	{
		// argument is not of appropriate type, attempt to coerce it
		sc = VariantChangeType(&va, pArg, 0, pEntry->vt);
		if (FAILED(sc))
		{
			TRACE0("Warning: automation property coercion failed.\n");
			*puArgErr = 0;
			return sc;
		}
		ASSERT(va.vt == pEntry->vt);
		pArg = &va;
	}

	void* pProp = (BYTE*)this + pEntry->nPropOffset;
	switch (pEntry->vt)
	{
	case VT_I1:
		*(BYTE*)pProp = pArg->bVal;
		break;
	case VT_I2:
		*(short*)pProp = pArg->iVal;
		break;
	case VT_I4:
		*(long*)pProp = pArg->lVal;
		break;
	case VT_R4:
		*(float*)pProp = pArg->fltVal;
		break;
	case VT_R8:
		*(double*)pProp = pArg->dblVal;
		break;
	case VT_DATE:
		*(double*)pProp = pArg->date;
		break;
	case VT_CY:
		*(CY*)pProp = pArg->cyVal;
		break;
	case VT_BSTR:
		AfxBSTR2CString((CString*)pProp, pArg->bstrVal);
		break;
	case VT_ERROR:
		*(SCODE*)pProp = pArg->scode;
		break;
	case VT_BOOL:
		*(BOOL*)pProp = (V_BOOL(pArg) != 0);
		break;
	case VT_VARIANT:
		if (VariantCopy((LPVARIANT)pProp, pArg) != S_OK)
			*puArgErr = 0;
		break;
	case VT_DISPATCH:
	case VT_UNKNOWN:
		if (pArg->punkVal != NULL)
			pArg->punkVal->AddRef();
		_AfxRelease((LPUNKNOWN*)pProp);
		*(LPUNKNOWN*)pProp = pArg->punkVal;
		break;

	default:
		*puArgErr = 0;
		sc = DISP_E_BADVARTYPE;
	}
	VariantClear(&va);

	// if property was a DISP_PROPERTY_NOTIFY type, call pfnSet after setting
	if (!FAILED(sc) && pEntry->pfnSet != NULL)
	{
		AFX_MANAGE_STATE(m_pModuleState);
		(this->*pEntry->pfnSet)();
	}

	return sc;
}