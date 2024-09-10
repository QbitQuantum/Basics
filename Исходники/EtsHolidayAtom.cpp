//return holidays in array
STDMETHODIMP CEtsHolidayAtom::GetHolidays(DATE dtToday, SAFEARRAY ** psaDates,  LONG* pnCount)
{

	if (!pnCount) return E_POINTER;

	*pnCount = static_cast<LONG>( m_vHoliday.size() );

	if (*pnCount > 0)
	{
		LPSAFEARRAY pDates = SafeArrayCreateVector(VT_R8, 0, *pnCount);
		::SafeArrayLock(pDates);
		
		LPVOID lpDateData = NULL;
		::SafeArrayAccessData(pDates, &lpDateData);
		

		DOUBLE * pdDates =	 reinterpret_cast<DOUBLE *>(lpDateData);
		for(long i = 0; i< *pnCount; i++)
		{
			pdDates[i] = m_vHoliday[i];
		}

		::SafeArrayUnaccessData(pDates);
		::SafeArrayUnlock(pDates);

		*psaDates = pDates;
	}

	return S_OK;
}