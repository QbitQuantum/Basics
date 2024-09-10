STDMETHODIMP CBDictionary::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams,
		VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
	if((dispIdMember & 0xff000000) != 0x65000000)
		return CBDispatch<IVariantDictionary>::g_typeinfo.Invoke((IVariantDictionary*)this, dispIdMember, wFlags,
			pDispParams, pVarResult, pExcepInfo, puArgErr);

	dispIdMember &= 0xffffff;

	CBLock l(&m_cs);

	if(dispIdMember < (int)m_posArray.GetCount())
	{
		if((wFlags & (DISPATCH_PROPERTYPUT | DISPATCH_PROPERTYPUTREF)) && pDispParams->cArgs == 1)
		{
			VARIANT* pvar = pDispParams->rgvarg;

			while(pvar->vt == (VT_VARIANT | VT_BYREF))
				pvar = pvar->pvarVal;

			if(!(wFlags & DISPATCH_PROPERTYPUTREF) &&
				(pvar->vt == VT_UNKNOWN || pvar->vt == VT_DISPATCH))
			{
				l.Unlock();

				if(pvar->punkVal == NULL)
					return DISP_E_UNKNOWNINTERFACE;

				CBDispatchPtr pDisp;
				CComVariant var;

				HRESULT hr = pvar->punkVal->QueryInterface(&pDisp);
				if(FAILED(hr))return hr;

				hr = pDisp.GetProperty(0, &var);
				if(FAILED(hr))return hr;

				l.Lock();
				if(dispIdMember < (int)m_posArray.GetCount())
				{
					var.Detach(&m_posArray[dispIdMember]->m_value);
					return S_OK;
				}else return DISP_E_MEMBERNOTFOUND;
			}else return VariantCopyInd(&m_posArray[dispIdMember]->m_value, pvar);
		}else if(pDispParams->cArgs == 0)
		{
			if(pVarResult != NULL)
				return VariantCopy(pVarResult, &m_posArray[dispIdMember]->m_value);

			return S_OK;
		}

		VARIANT *pvar = &m_posArray[dispIdMember]->m_value;

		if(pvar->vt == VT_UNKNOWN || pvar->vt == VT_DISPATCH)
		{
			CBDispatchPtr pDisp;

			HRESULT hr = pvar->punkVal->QueryInterface(&pDisp);
			if(FAILED(hr))
				return DISP_E_BADPARAMCOUNT;

			l.Unlock();
			return pDisp->Invoke(0, riid, lcid, wFlags, pDispParams,
					pVarResult, pExcepInfo, puArgErr);
		}

		return DISP_E_BADPARAMCOUNT;
	}else return DISP_E_MEMBERNOTFOUND;

	return S_OK;
}