	// IUICommandhandler Implementation
	STDMETHODIMP CConfigDialogApplication::Execute(UINT nCmdID,												/*Control ID*/
						UI_EXECUTIONVERB verb,										/*Action or Event*/
						__in_opt const PROPERTYKEY* key,							/*Property Changing*/
						__in_opt const PROPVARIANT* ppropvarValue,					/*Value of the propery changing*/
						__in_opt IUISimplePropertySet* pCommandExecutionProperties)
	{
		UNREFERENCED_PARAMETER(pCommandExecutionProperties);
		m_hr = S_OK;
		
		switch (verb)//Action switch
		{
		case UI_EXECUTIONVERB_EXECUTE:
		case UI_EXECUTIONVERB_PREVIEW:
		case UI_EXECUTIONVERB_CANCELPREVIEW:
			{
			switch( nCmdID )//Control switch
			{
			case cmdVSync:
				{
					PROPVARIANT var, varNew;

					m_hr = pRibbonFramework->GetUICommandProperty(cmdVSync, UI_PKEY_BooleanValue, &var);
					if (FAILED(m_hr))
					   return m_hr;

					m_hr = PropVariantToBoolean(var, &m_VSyncEnable);
					if (FAILED(m_hr))
					   return m_hr;

					m_VSyncEnable = !m_VSyncEnable;
					m_hr = UIInitPropertyFromBoolean(UI_PKEY_Enabled, m_VSyncEnable, &varNew);
					if (FAILED(m_hr))
					   return m_hr;

					m_hr = pRibbonFramework->InvalidateUICommand(cmdVSync, UI_INVALIDATIONS_PROPERTY, &UI_PKEY_Label);
					if (FAILED(m_hr))
						return m_hr;
				}
				break;
			case cmdFTS:
				{
					m_FTSEnable = !m_FTSEnable;
					
					m_hr = pRibbonFramework->InvalidateUICommand(cmdFTS, UI_INVALIDATIONS_PROPERTY, &UI_PKEY_Label);
					m_hr = pRibbonFramework->InvalidateUICommand(cmdFT,  UI_INVALIDATIONS_PROPERTY, &UI_PKEY_Enabled);
					if (FAILED(m_hr))
						return m_hr;
				}
				break;

			}//End Control switch

			}
			break;

		}//End Action Switch

		return m_hr;
	}