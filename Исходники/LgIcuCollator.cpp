/*----------------------------------------------------------------------------------------------
	Ensure that we have a collator.
----------------------------------------------------------------------------------------------*/
void LgIcuCollator::EnsureCollator()
{
	if (m_pCollator)
		return; // we already have one.
	UErrorCode uerr = U_ZERO_ERROR;
	if (m_stuLocale.Length() == 0)
	{
		m_pCollator = Collator::createInstance(uerr);
	}
	else
	{
		StrAnsi sta(m_stuLocale.Bstr());
		char rgchLoc[128];
		int32_t cch = uloc_getName(sta.Chars(), rgchLoc, sizeof(rgchLoc), &uerr);
		Assert(cch < 128);
		rgchLoc[cch] = 0;
		if (U_FAILURE(uerr))
			ThrowHr(E_FAIL);
		const Locale loc = Locale::createFromName (rgchLoc);
		m_pCollator = Collator::createInstance (loc, uerr);
	}
	if (U_FAILURE(uerr))
		ThrowHr(E_FAIL);
}