//*****************************************************************************
//* Function Name: DecodeProperty
//*   Description: Decode a single property value. We support a small number
//*                of simple data types. Having converted the string value
//*                to a particular data type, hand it off to one of two
//*                property descriptors - either p_pPropertyDescriptor which
//*                holds a single value or p_pPropertyArrayDescriptor which
//*                holds a vector of values (of the same type).
//*****************************************************************************
void CEntityDecoder::DecodeProperty (
	const _bstr_t&					p_sbstrValue,
	bool							p_bPropertyArray,
	const CPropertyDescriptor*		p_pPropertyDescriptor,
	const CPropertyArrayDescriptor*	p_pPropertyArrayDescriptor)
{
	_variant_t l_svarValue (p_sbstrValue);

	_ASSERTE (
		(p_bPropertyArray == true  && p_pPropertyDescriptor == NULL && p_pPropertyArrayDescriptor != NULL) ||
		(p_bPropertyArray == false && p_pPropertyDescriptor != NULL && p_pPropertyArrayDescriptor == NULL));

	const type_info& l_tiPropertyType =
		(p_bPropertyArray)
			? p_pPropertyArrayDescriptor->GetPropertyType ()
			: p_pPropertyDescriptor->GetPropertyType ();

	if (l_tiPropertyType == typeid (_bstr_t)) {
		_bstr_t l_sbstrValue = l_svarValue;
		if (p_bPropertyArray)
			p_pPropertyArrayDescriptor->AddPropertyValue (l_sbstrValue);
		else
			p_pPropertyDescriptor->SetPropertyValue (l_sbstrValue);
	}
	else if (l_tiPropertyType == typeid (double)) {
		double l_dblValue = l_svarValue;
		if (p_bPropertyArray)
			p_pPropertyArrayDescriptor->AddPropertyValue (l_dblValue);
		else
			p_pPropertyDescriptor->SetPropertyValue (l_dblValue);
	}
	else if (l_tiPropertyType == typeid (long)) {
		long l_lValue = l_svarValue;
		if (p_bPropertyArray)
			p_pPropertyArrayDescriptor->AddPropertyValue (l_lValue);
		else
			p_pPropertyDescriptor->SetPropertyValue (l_lValue);
	}
	else if (l_tiPropertyType == typeid (bool)) {
		bool l_bValue = l_svarValue;
		if (p_bPropertyArray)
			p_pPropertyArrayDescriptor->AddPropertyValue (l_bValue);
		else
			p_pPropertyDescriptor->SetPropertyValue (l_bValue);
	}
	else {
		USES_CONVERSION;
		LPCTSTR l_lpszPropertyTypeName = A2CT (l_tiPropertyType.name ());
		ThrowComErrorException (
			__FILE__,
			__LINE__,
			E_UNEXPECTED,
			IDS_UNSUPPORTED_PROPERTY_DATA_TYPE,
			l_lpszPropertyTypeName);
	}
}