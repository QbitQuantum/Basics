LRESULT xRenderSettingPane::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	CMFCPropertyGridProperty * prop = (CMFCPropertyGridProperty *)lParam;
	IPropertyObj * obj = xRenderSetting::Instance();

	const char * name = prop->GetName();

	const Property * p = obj->GetProperty(name);

	if (p)
	{
		char cdata[128];
		const COleVariant & strValue = prop->GetValue();
		CString val = (CString)strValue;

		Strcpy(cdata, 128, (const char *)val);

		if (p->type == PT_Bool)
		{
			bool bdata = (strValue.boolVal == -1);
			obj->SetPropertyData(p, &bdata);
		}
		else if (p->type == PT_Int && p->enumObj)
		{
			const cEnum * e = p->enumObj->GetEnum(cdata);
			obj->SetPropertyData(p, &e->val);
		}
	}


	return S_OK;
}