HRESULT
ceTranslatePeriodUnits(
    IN WCHAR const *pwszPeriod,
    IN LONG lCount,
    OUT enum ENUM_PERIOD *penumPeriod,
    OUT LONG *plCount)
{
    HRESULT hr;
    UNITSTABLE const *put;

    for (put = g_aut; put < &g_aut[CUNITSTABLEMAX]; put++)
    {
	if (0 == celstrcmpiL(pwszPeriod, put->pwszString))
	{
	    *penumPeriod = put->enumPeriod;
	    if (0 > lCount)
	    {
		lCount = MAXLONG;
	    }
	    *plCount = lCount;
	    hr = S_OK;
	    goto error;
	}
    }
    hr = HRESULT_FROM_WIN32(ERROR_INVALID_DATA);

error:
    return(hr);
}