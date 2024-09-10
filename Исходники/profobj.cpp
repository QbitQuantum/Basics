STDMETHODIMP CAvatarProfileObject::AddKey(BSTR bstrKey, VARIANT varKeyVal, VARIANT varStrGraphic, VARIANT varAccess, VARIANT varOwner)
{
	HRESULT hr = S_OK;
	CComVariant varTemp;
	long psbits = 0;
	IThing* pUser = NULL;
	IThing* pCaller = NULL;
	IThing* pOwner = NULL;
	IAvatarProfileData* pProfileData = NULL;
	VARIANT_BOOL bShouldExecute = VARIANT_TRUE;
	VARIANT_BOOL bShouldRemote = VARIANT_FALSE;
	VARIANT_BOOL bShouldNotify = VARIANT_FALSE;

	// REVIEW: should really create an AddKeyExt method which takes the real datatypes

	hr = VariantCopyInd(&varTemp, &varKeyVal);
	if (FAILED(hr))
		goto ERROR_ENCOUNTERED;

	if (m_pWorld)
	{
		hr = m_pWorld->ValidateProperty(varTemp);
		if (FAILED(hr))
			goto ERROR_ENCOUNTERED;
	}

	GetMarshallingFlags(&bShouldExecute, &bShouldRemote, &bShouldNotify);

	if (bShouldRemote == VARIANT_TRUE)
		GetMarshallingBits(&psbits, &bShouldExecute, &bShouldRemote, &bShouldNotify);

#ifdef _DEBUG
	VWTRACE(m_pWorld, "VWPROPERTY", VWT_METHOD, "CAvatarProfileObject::AddKey\n");
#endif

	if (bShouldExecute == VARIANT_TRUE)
	{
		VARIANT_BOOL bValid = VARIANT_FALSE;
		CComBSTR bstrGraphic;
		short sAccess = 0;

		if (m_pParent)
		{
			if (FAILED(m_pParent->CheckPropertySecurityExt(m_bstrPropertyName, PS_WRITE)))
			{
				VWTRACE(m_pWorld, "VWOBJECT", VWT_ERROR, "CAvatarProfileObject::AddKey: security violation (PS_WRITE)\n");
				hr = VWOBJECT_E_PERMISSION_DENIED;
				goto ERROR_ENCOUNTERED;
			}
		}

		if (m_pKeys == NULL)
		{
			VWTRACE(m_pWorld, "VWPROPERTY", VWT_ERROR, "CAvatarProfileObject::AddKey: invalid key map\n");
			hr = VWAVATARPROFILE_E_INVALIDKEYMAP;
			goto ERROR_ENCOUNTERED;
		}

		if (m_pBannedObjects == NULL)
		{
			VWTRACE(m_pWorld, "VWPROPERTY", VWT_ERROR, "CAvatarProfileObject::AddKey: invalid banned object list\n");
			hr = VWAVATARPROFILE_E_INVALIDBANNEDOBJECTLIST;
			goto ERROR_ENCOUNTERED;
		}

		// if user isn't avatar
		if (bShouldRemote == VARIANT_TRUE)
		{
			hr = m_pWorld->get_User(&pUser);
			if (FAILED(hr))
				goto ERROR_ENCOUNTERED;

			// we are the originator - check protocol
			if (pUser && m_pAvatar && (pUser != m_pAvatar))
			{
				long lIndex = -1;

				/* hr = */ m_pBannedObjects->Find(CComVariant(pUser), &lIndex);

				// if user is banned object, fail
				if (lIndex != -1)
				{
					VWTRACE(m_pWorld, "VWPROPERTY", VWT_ERROR, "CAvatarProfileObject::AddKey: user is banned object, failed to add key\n");
					hr = VWAVATARPROFILE_E_BANNEDOBJECT;
					goto ERROR_ENCOUNTERED;
				}
			}
		}

		// if key already exists, fail
		hr = m_pKeys->IsValid(bstrKey, &bValid);
		if (FAILED(hr))
			goto ERROR_ENCOUNTERED;

		if (bValid == VARIANT_TRUE)
		{
#ifdef _DEBUG
			VWTRACE(m_pWorld, "VWPROPERTY", VWT_IMPORTANT, "CAvatarProfileObject::AddKey: key (%s) already exists, failed to add key\n", CString(bstrKey));
#endif
			hr = VWAVATARPROFILE_E_KEYEXISTS;
			goto ERROR_ENCOUNTERED;
		}

		// add the property..
		pProfileData = new CComAvatarProfileData;
		if (pProfileData == NULL)
			goto ERROR_ENCOUNTERED;

		pProfileData->AddRef();

		/* hr = */ pProfileData->put_World(m_pWorld);

		// now, create the optional data items
		if (varStrGraphic.vt == VT_BSTR)
			bstrGraphic = varStrGraphic.bstrVal;
		
		if ((varAccess.vt == VT_EMPTY) || (varAccess.vt == VT_ERROR))
			sAccess = kKeyPublic;
		else
		{
			CComVariant varI2;

			::VariantChangeType(&varI2, &varAccess, 0, VT_I2);
			ASSERT(varI2.vt == VT_I2);

			sAccess = (short)varI2.iVal;
		}

		if (varOwner.vt == VT_DISPATCH)
		{
			pOwner = (IThing *)varOwner.pdispVal;
			SAFEADDREF(pOwner);
		}
		else
		{
			// if no owner passed in, set owner to be avatar
			pOwner = m_pAvatar;
			SAFEADDREF(pOwner);
		}

		// can only set the owner to the user
		if (bShouldRemote == VARIANT_TRUE)
		{
			// REVIEW: why are we resetting the owner?

			hr = m_pWorld->get_Caller(&pCaller);
			if (FAILED(hr))
				goto ERROR_ENCOUNTERED;

			// check protocol:
			// otherwise, make sure passed in owner is either user or caller
			if ((pOwner != NULL) && (pUser != NULL) && (pCaller != NULL) && (pOwner != pUser) && (pOwner != pCaller))
			{
#ifdef _DEBUG
				CComBSTR bstrUser("n/a"), bstrCaller("n/a"), bstrOwner("n/a");

				/* hr = */ pUser->get_Name(&bstrUser.m_str);
				/* hr = */ pCaller->get_Name(&bstrCaller.m_str);
				/* hr = */ pOwner->get_Name(&bstrOwner.m_str);

				VWTRACE(m_pWorld, "VWPROPERTY", VWT_ERROR, "CAvatarProfileObject::AddKey: invalid owner (not user or caller), user (%s), caller (%s), owner (%s)\n", 
					CString(bstrUser), CString(bstrCaller), CString(bstrOwner));
#endif

				hr = VWAVATARPROFILE_E_INVALIDOWNER;
				goto ERROR_ENCOUNTERED;
			}
		}

		/* hr = */ pProfileData->put_Value(varTemp);
		/* hr = */ pProfileData->put_Owner(pOwner);
		/* hr = */ pProfileData->put_Graphic(bstrGraphic);
		/* hr = */ pProfileData->put_Access(sAccess);

		hr = m_pKeys->put_ObjectProperty(bstrKey, pProfileData);
		if (FAILED(hr))
			goto ERROR_ENCOUNTERED;
	}

	// remote
	if (bShouldRemote == VARIANT_TRUE)
	{
		DISPPARAMS dispparams;

		// package up args into DISPPARAMS struct
		hr = InitializeDISPPARAMS(&dispparams, 5);
		if (FAILED(hr))
			goto ERROR_ENCOUNTERED;

		dispparams.rgvarg[4].vt = VT_BSTR;
		dispparams.rgvarg[4].bstrVal = bstrKey;
		dispparams.rgvarg[3] = varTemp;
		dispparams.rgvarg[2] = varStrGraphic;
		dispparams.rgvarg[1] = varAccess;
		dispparams.rgvarg[0] = varOwner;

		hr = SendObjectPropertyCommand(psbits, DISPID_AVATARPROFILE_ADDKEY, DISPATCH_METHOD, &dispparams);

		TerminateDISPPARAMS(VARIANT_FALSE, &dispparams);

		if (FAILED(hr))
			goto ERROR_ENCOUNTERED;
	}

	// Notify
	if (bShouldNotify == VARIANT_TRUE)
	{
		// notify client/server and world of property change
		if (m_pParent)
		{
			hr = m_pParent->NotifyObjectPropertyChanged(this, profileAddKey, CComVariant(bstrKey));
			if (FAILED(hr))
				goto ERROR_ENCOUNTERED;
		}
	}
	
ERROR_ENCOUNTERED:
	SAFERELEASE(pOwner);
	SAFERELEASE(pUser);
	SAFERELEASE(pCaller);
	SAFERELEASE(pProfileData);
	
	return hr;
}