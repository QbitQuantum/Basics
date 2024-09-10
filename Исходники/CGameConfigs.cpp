SMCResult CGameConfig::ReadSMC_LeavingSection(const SMCStates *states)
{
	if (m_IgnoreLevel)
	{
		m_IgnoreLevel--;
		return SMCResult_Continue;
	}

	if (m_CustomLevel)
	{
		m_CustomLevel--;
		m_CustomHandler->ReadSMC_LeavingSection(states);
		return SMCResult_Continue;
	}

	switch (m_ParseState)
	{
		case PSTATE_GAMES:
		{
			m_ParseState = PSTATE_NONE;
			break;
		}
		case PSTATE_GAMEDEFS:
		{
			m_ParseState = PSTATE_GAMES;
			break;
		}
		case PSTATE_GAMEDEFS_CLASSES:
		{
			m_MatchedClasses = false;
			m_ParseState = PSTATE_GAMEDEFS;
			break;
		}
		case PSTATE_GAMEDEFS_CLASSES_CLASS:
		{
			m_ParseState = PSTATE_GAMEDEFS_CLASSES;
			m_Class[0] = '\0';
			break;
		}
		case PSTATE_GAMEDEFS_CUSTOM:
		{
			m_ParseState = PSTATE_GAMEDEFS;
			m_CustomHandler->ReadSMC_ParseEnd(false, false);
			break;
		}
		case PSTATE_GAMEDEFS_KEYS:
		{
			m_ParseState = m_MatchedClasses ? PSTATE_GAMEDEFS_CLASSES_CLASS : PSTATE_GAMEDEFS;
			break;
		}
		case PSTATE_GAMEDEFS_OFFSETS:
		{
			m_ParseState = m_MatchedClasses ? PSTATE_GAMEDEFS_CLASSES_CLASS : PSTATE_GAMEDEFS;
			break;
		}
		case PSTATE_GAMEDEFS_OFFSETS_OFFSET:
		{
			if (m_FoundOffset)
			{
				if (m_Class[0])
				{
					auto ic = m_OffsetsByClass.findForAdd(m_Class);

					if (ic.found())
					{
						ic->value->list.replace(m_Offset, TempType);
					}
					else if (m_OffsetsByClass.add(ic, m_Class))
					{
						ic->value = new OffsetClass;
						ic->value->list.insert(m_Offset, TempType);
					}
				}
				else
				{
					m_Offsets.replace(m_Offset, TempType);
				}
			}

			m_ParseState = PSTATE_GAMEDEFS_OFFSETS;
			break;
		}
		case PSTATE_GAMEDEFS_SUPPORTED:
		{
			if (!m_ShouldBeReadingDefault)
			{
				m_IgnoreLevel = 1;
				m_ParseState = PSTATE_GAMES;
			}
			else
			{
				m_ParseState = PSTATE_GAMEDEFS;
			}
			break;
		}
		case PSTATE_GAMEDEFS_SIGNATURES:
		{
			m_ParseState = m_MatchedClasses ? PSTATE_GAMEDEFS_CLASSES_CLASS : PSTATE_GAMEDEFS;
			break;
		}
		case PSTATE_GAMEDEFS_SIGNATURES_SIG:
		{
			if (TempSig.library[0] == '\0')
			{
				strncopy(TempSig.library, "server", sizeof(TempSig.library));
			}

			void *addressInBase = nullptr;

			if (strcmp(TempSig.library, "server") == 0)
			{
				addressInBase = reinterpret_cast<void*>(MDLL_Spawn);
			}
			else if (strcmp(TempSig.library, "engine") == 0)
			{
				addressInBase = reinterpret_cast<void*>(gpGlobals);
			}

			void *finalAddress = nullptr;

			if (!addressInBase)
			{
				AMXXLOG_Error("Unrecognized library \"%s\" (gameconf \"%s\")", TempSig.library, m_CurrentPath);
			}
			else if (TempSig.signature[0])
			{
				if (TempSig.signature[0] == '@')
				{
#if defined PLATFORM_WINDOWS
					MEMORY_BASIC_INFORMATION mem;

					if (VirtualQuery(addressInBase, &mem, sizeof(mem)))
					{
						finalAddress = g_MemUtils.ResolveSymbol(mem.AllocationBase, &TempSig.signature[1]);
					}
					else
					{
						AMXXLOG_Error("Unable to find library \"%s\" in memory (gameconf \"%s\")", TempSig.library, m_File);
					}

#elif defined PLATFORM_POSIX
					Dl_info info;

					if (dladdr(addressInBase, &info) != 0)
					{
						void *handle = dlopen(info.dli_fname, RTLD_NOW);

						if (handle)
						{
							finalAddress = g_MemUtils.ResolveSymbol(handle, &TempSig.signature[1]);
							dlclose(handle);
						}
						else
						{
							AMXXLOG_Error("Unable to load library \"%s\" (gameconf \"%s\")", TempSig.library, m_File);
						}
					}
					else
					{
						AMXXLOG_Error("Unable to find library \"%s\" in memory (gameconf \"%s\")", TempSig.library, m_File);
					}
#endif
				}

				if (!finalAddress)
				{
					finalAddress = g_MemUtils.DecodeAndFindPattern(addressInBase, TempSig.signature);
				}

				m_Sigs.replace(m_Offset, finalAddress);
			}

			m_ParseState = PSTATE_GAMEDEFS_SIGNATURES;
			break;
		}
		case PSTATE_GAMEDEFS_ADDRESSES:
		{
			m_ParseState = m_MatchedClasses ? PSTATE_GAMEDEFS_CLASSES_CLASS : PSTATE_GAMEDEFS;
			break;
		}
		case PSTATE_GAMEDEFS_ADDRESSES_ADDRESS:
		{
			m_ParseState = PSTATE_GAMEDEFS_ADDRESSES;

			if (m_Address[0] != '\0' && m_AddressSignature[0] != '\0')
			{
				AddressConf addrConf(m_AddressSignature, sizeof(m_AddressSignature), m_AddressReadCount, m_AddressRead);
				m_Addresses.replace(m_Address, addrConf);
			}

			break;
		}
		case PSTATE_GAMEDEFS_ADDRESSES_ADDRESS_READ:
		{
			m_ParseState = PSTATE_GAMEDEFS_ADDRESSES_ADDRESS;
			break;
		}
	}

	return SMCResult_Continue;
}