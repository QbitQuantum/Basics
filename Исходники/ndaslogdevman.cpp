HRESULT
CNdasLogicalUnitManager::Register(INdasUnit* pNdasUnit, INdasLogicalUnit** ppNdasLogicalUnit)
{
	HRESULT hr;

	XTLTRACE2(NDASSVC_NDASLOGDEVMANAGER, TRACE_LEVEL_INFORMATION, 
		"Registering NdasUnit=%p to LDM\n", pNdasUnit);

	*ppNdasLogicalUnit = NULL;

	NDAS_LOGICALDEVICE_GROUP ludef;
	COMVERIFY(pNdasUnit->get_LogicalUnitDefinition(&ludef));

	DWORD luseq;
	COMVERIFY(pNdasUnit->get_LogicalUnitSequence(&luseq));

	CComPtr<INdasLogicalUnit> pNdasLogicalUnit;

	LockInstance();

	LogicalDeviceGroupMap::iterator itr = m_LogicalUnitDefinitionMap.find(ludef);

	if (itr == m_LogicalUnitDefinitionMap.end()) 
	{
		//
		// New Logical Device Instance
		//
		NDAS_LOGICALDEVICE_ID id = pAllocateID();
		if (0 == id) 
		{
			UnlockInstance();
			// SLOT FULL
			hr = NDASSVC_ERROR_LOGICALDEVICE_SLOT_FULL;
			return hr;
		}

		CComObject<CNdasLogicalUnit>* pNdasLogicalUnitInstance;
		hr = CComObject<CNdasLogicalUnit>::CreateInstance(&pNdasLogicalUnitInstance);
		if (FAILED(hr))
		{
			XTLTRACE2(NDASSVC_NDASLOGDEVMANAGER, TRACE_LEVEL_ERROR, 
				"CNdasLogicalUnit::CreateInstance failed, hr=0x%X\n", hr);
			UnlockInstance();
			return hr;
		}

		hr = pNdasLogicalUnitInstance->Initialize(id, ludef);
		if (FAILED(hr))
		{
			XTLTRACE2(NDASSVC_NDASLOGDEVMANAGER, TRACE_LEVEL_ERROR, 
				"CNdasLogicalUnit::Initialize failed, hr=0x%X\n", hr);
			UnlockInstance();
			return hr;
		}

		pNdasLogicalUnit = pNdasLogicalUnitInstance;

		m_NdasLogicalUnits.Add(pNdasLogicalUnit);
		m_LogicalUnitDefinitionMap.insert(std::make_pair(ludef, pNdasLogicalUnit));
		m_LogicalUnitIdMap.insert(std::make_pair(id, pNdasLogicalUnit));

		UnlockInstance();

		CComPtr<INdasDevice> pNdasDevice;
		COMVERIFY(pNdasUnit->get_ParentNdasDevice(&pNdasDevice));
		XTLASSERT(pNdasDevice);

		DWORD regFlags;
		COMVERIFY(pNdasDevice->get_RegisterFlags(&regFlags));

		if (regFlags & NDAS_DEVICE_REG_FLAG_AUTO_REGISTERED) 
		{
			BOOL fMountOnReady = TRUE;
			if (NdasServiceConfig::Get(nscMountOnReadyForEncryptedOnly))
			{
				NDAS_UNITDEVICE_TYPE unitType;
				COMVERIFY(pNdasUnit->get_Type(&unitType));

				if (0 == luseq && NDAS_UNITDEVICE_TYPE_DISK == unitType)
				{
					CComQIPtr<INdasDiskUnit> pNdasDiskUnit(pNdasUnit);
					ATLASSERT(pNdasDiskUnit.p);

					NDAS_CONTENT_ENCRYPT encryption;
					COMVERIFY(pNdasDiskUnit->get_ContentEncryption(&encryption));

					if (NDAS_CONTENT_ENCRYPT_METHOD_NONE != encryption.Method)
					{
						fMountOnReady = TRUE;
					}
					else
					{
						fMountOnReady = FALSE;
					}
				}
			}

			// auto registered devices always ignore RiskyMountFlag
			pNdasLogicalUnit->SetRiskyMountFlag(FALSE);

			if (fMountOnReady)
			{
				ACCESS_MASK granted;
				pNdasDevice->get_GrantedAccess(&granted);
				pNdasLogicalUnit->SetMountOnReady(granted, FALSE);
			}
		}

	}
	else 
	{
		pNdasLogicalUnit = itr->second;
		UnlockInstance();
	}

	COMVERIFY(pNdasLogicalUnit->AddNdasUnitInstance(pNdasUnit));

	*ppNdasLogicalUnit = pNdasLogicalUnit.Detach();

	return S_OK;
}