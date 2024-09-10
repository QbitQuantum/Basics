bstr_t Distribution::MapArenaDistribution() 
{
	CComBSTR bstr;
	// See if distribution reference.
	// FIXME: check if distreference exists in distributions
	MappedValues & mymappedvalues(this->mappedvalues);
	if(distreference!=_bstr_t(L"None"))
	{
		bstr = (BSTR) distributions[distreference].distname;
		mymappedvalues=MappedValues(distributions[distreference].mappedvalues);
	}
	else 
		bstr = (BSTR) distname;

	bstr.ToLower();
	bstr_t arenaexpr;
	if(bstr ==  L"exponential")
	{
		arenaexpr=L"EXPO(" + mymappedvalues[L"mean"] + L")";
		
	}
	if(bstr ==  L"poisson")
	{
		arenaexpr=L"POIS(" + mymappedvalues[L"mean"] + L")";
		
	}
	else	if(bstr ==  L"normal")
	{
		arenaexpr=L"NORM(" + mymappedvalues[L"mean"] +  L"," + mymappedvalues[L"deviation"] + L")";
		
	}
	else if(bstr == L"weibull")
	{
		arenaexpr=L"WEIB(" + mymappedvalues[L"scale"] + L"," + mymappedvalues[L"shape"] + ")";
	}
	else if(bstr == L"gamma")
	{
		arenaexpr=L"GAMM(" + mappedvalues[L"scale"] + L"," + mappedvalues[L"shape"] + ")";
	}
	else if(bstr == L"triagle")
	{
		arenaexpr=L"TRIA(" + mymappedvalues[L"minimum"] + L"," ;
		arenaexpr+=  mymappedvalues[L"mode"] + L",";
		arenaexpr+= mymappedvalues[L"maximum"] + L")";
	}
	return arenaexpr;
}