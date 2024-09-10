PLUGIN_EXPORT double Update(void* data)
{
	if (g_pInterface == nullptr) return 0;

	MeasureData* measure = (MeasureData*)data;
	double value = 0;

	if (measure->type != UNKNOWN)
	{
		if (measure->type == LIST)
		{
			PWLAN_AVAILABLE_NETWORK_LIST pwnl = nullptr;
			DWORD dwErr = WlanGetAvailableNetworkList(g_hClient, &g_pInterface->InterfaceGuid, 0, nullptr, &pwnl);

			if (ERROR_SUCCESS != dwErr)
			{
				measure->statusString = L"Error";
			}
			else
			{
				// Size of network name can be up to 64 chars, set to 80 to add room for delimiters
				measure->statusString.clear();
				measure->statusString.reserve(80 * measure->listMax);

				UINT printed = 0;  // count of how many networks have been printed already

				// Check all items in WLAN NETWORK LIST
				for (size_t i = 0; i < pwnl->dwNumberOfItems ; ++i)
				{
					if (printed == measure->listMax) break;

					// SSID is in UCHAR, convert to WCHAR
					std::wstring ssid = ConvertToWide((LPCSTR)pwnl->Network[i].dot11Ssid.ucSSID, (int)pwnl->Network[i].dot11Ssid.uSSIDLength);

					// Prevent duplicates that result from profiles, check using SSID
					if (!ssid.empty() && ssid[0] && wcsstr(measure->statusString.c_str(), ssid.c_str()) == nullptr)
					{
						++printed;
						measure->statusString += ssid;
						if (measure->listStyle > 0)
						{
							if (measure->listStyle == 1 || measure->listStyle == 3)
							{
								// ADD PHY type
								measure->statusString += L" @";
								measure->statusString += ToString(pwnl->Network[i].dot11PhyTypes[0]);
							}
							if (measure->listStyle == 2 || measure->listStyle == 3)
							{
								// ADD cipher and authentication
								measure->statusString += L" (";
								measure->statusString += ToString(pwnl->Network[i].dot11DefaultCipherAlgorithm);
								measure->statusString += L':';
								measure->statusString += ToString(pwnl->Network[i].dot11DefaultAuthAlgorithm);
								measure->statusString += L')';
							}
						}
						measure->statusString += L'\n';
					}
				}

				WlanFreeMemory(pwnl);
			}
		}
		else if (measure->type == TXRATE)
		{
			DWORD dwErr = getAdapterAddresses(&g_pAddresses);
			if (NO_ERROR != dwErr) {
				measure->statusString = L"Error";
				value = (double)-1;
			}
			else
			{
				PIP_ADAPTER_ADDRESSES pCurrAddresses = g_pAddresses;
				value = (double)-1;
				while(pCurrAddresses)
				{
					// Doesn't work - not sure how to compare the 2 GUIDs
					// if (pCurrAddresses->NetworkGuid != g_pInterface->InterfaceGuid)
					// Ignores the interface index parameter - whoops.
					if (IF_TYPE_IEEE80211 != pCurrAddresses->IfType)
					{
						pCurrAddresses = pCurrAddresses->Next;
						continue;
					}
					value = (double)pCurrAddresses->TransmitLinkSpeed;
					break;
				}
			}
			if (g_pAddresses != nullptr)
			{
				FREE(g_pAddresses);
			}
		}
		else
		{
			ULONG outsize = 0;
			PWLAN_CONNECTION_ATTRIBUTES wlan_cattr = nullptr;
			DWORD dwErr = WlanQueryInterface(g_hClient, &g_pInterface->InterfaceGuid, wlan_intf_opcode_current_connection, nullptr, &outsize, (PVOID*)&wlan_cattr, nullptr);

			if (ERROR_SUCCESS != dwErr)
			{
				switch (measure->type)
				{
				case SSID:
				case PHY:
				case ENCRYPTION:
				case AUTH:
					measure->statusString = L"-1";
					break;
				}
			}
			else
			{
				switch (measure->type)
				{
// This rate is currently bogus, sadly :-(
//				case TXRATE:
//					value = (double)wlan_cattr->wlanAssociationAttributes.ulTxRate;
//					break;

				case QUALITY:
					value = (double)wlan_cattr->wlanAssociationAttributes.wlanSignalQuality;
					break;

				case SSID:
					// Need to convert ucSSID to wchar from uchar
					measure->statusString = ConvertToWide((LPCSTR)wlan_cattr->wlanAssociationAttributes.dot11Ssid.ucSSID, (int)wlan_cattr->wlanAssociationAttributes.dot11Ssid.uSSIDLength);
					// If not connected yet add current status
					measure->statusString += ToString(wlan_cattr->isState);
					break;

				case PHY:
					measure->statusString = ToString(wlan_cattr->wlanAssociationAttributes.dot11PhyType);
					break;

				case ENCRYPTION:
					measure->statusString = ToString(wlan_cattr->wlanSecurityAttributes.dot11CipherAlgorithm);
					break;

				case AUTH:
					measure->statusString = ToString(wlan_cattr->wlanSecurityAttributes.dot11AuthAlgorithm);
					break;

				default:  // Invalid type
					measure->statusString.clear();
					break;
				}

				WlanFreeMemory(wlan_cattr);
			}
		}
	}

	return value;
}