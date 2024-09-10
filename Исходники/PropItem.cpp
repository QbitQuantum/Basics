////////////////////////////////////////////////////////////////////////
// put_Value
//
HRESULT CDocProperty::put_Value(VARIANT *pvValue)
{
	VARIANT vtTmp; vtTmp.vt = VT_EMPTY;

	ODS(_T("CDocProperty::put_Value\n"));
	CHECK_NULL_RETURN(pvValue, E_POINTER);
	CHECK_FLAG_RETURN((m_fDeadObj || m_fRemovedItem), E_INVALIDOBJECT);

	// We don't support arrays (in this sample at least)...
	if ((pvValue->vt) & VT_ARRAY)
		return E_INVALIDARG;

	// Sanity check of VARTYPE (if it is not one we can save, don't bother)...
	switch (((pvValue->vt) & VT_TYPEMASK))
	{
	case VT_I2:
	case VT_I4:
	case VT_R4:
	case VT_R8:
	case VT_DATE:
	case VT_BSTR:
	case VT_BOOL:
		break;
	default:
		return E_INVALIDARG;
	}

	// Swap out the variant value and set the dirty flag. We make independent
	// copy of the VARIANT (performs indirection as needed)...
	m_fModified = TRUE;
	VariantClear(&m_vValue);
	return VariantCopyInd(&m_vValue, pvValue);
}