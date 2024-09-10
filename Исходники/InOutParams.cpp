STDMETHODIMP CInOutParams::mVariant(VARIANT a, VARIANT* b)
{
	VariantClear( b);
	return VariantCopy ( b, &a);
}