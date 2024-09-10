STDMETHODIMP CPyCOMTest::GetSetVariant(VARIANT var, VARIANT *out)
{
	VariantClear(out); // necessary?
	return VariantCopy(out, &var);
}