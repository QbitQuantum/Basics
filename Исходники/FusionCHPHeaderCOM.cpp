STDMETHODIMP CFusionCHPHeaderCOM::GetBackgroundZones(VARIANT *zones)
{
	VariantInit(zones);
	zones->vt = VT_ARRAY | VT_DISPATCH;
	zones->parray = NULL;
	affxchp::BackgroundZoneTypeList czones;
	header->GetBackgroundZones(czones);
	int nzones = (int)czones.size();
	SAFEARRAYBOUND  rgsaBound[1];
	rgsaBound[0].lLbound = 0;
	rgsaBound[0].cElements = nzones;
	zones->parray = SafeArrayCreate(VT_DISPATCH, 1, rgsaBound);
	long index=0;
	affxchp::BackgroundZoneTypeList::iterator it;
	for (it=czones.begin(); it!=czones.end(); ++it)
	{
		CComPtr<IBackgroundZoneType> z;
		z.CoCreateInstance(CLSID_BackgroundZoneType);
		CBackgroundZoneTypeCOM *pz = static_cast<CBackgroundZoneTypeCOM *>(z.p);
		pz->SetBg(*it);
		HRESULT hr = SafeArrayPutElement(zones->parray, &index, z);
		++index;
	}
	return S_OK;
}