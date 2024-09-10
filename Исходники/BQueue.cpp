STDMETHODIMP CBQueue::AddTail(VARIANT var)
{
	VARIANT varTemp = {VT_EMPTY};

	VariantCopyInd(&varTemp, &var);

	m_cs.Enter();
	m_listItems.AddTail(varTemp);
	m_cs.Leave();

	return S_OK;
}