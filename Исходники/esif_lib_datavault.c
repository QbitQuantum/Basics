// Write a Registry Key Value from an EsifData value
static eEsifError DataVault_WriteRegistry (
	DataVaultPtr self,
	esif_string keyname,
	EsifDataPtr value
	)
{
	eEsifError rc   = ESIF_E_UNSPECIFIED;
	HKEY hKey       = 0;
	DWORD dwFlags   = RRF_RT_ANY;
	DWORD dwError   = 0;
	DWORD dwSize    = 0;
	DWORD dwType    = REG_NONE;
	char *regkey    = 0;
	char *valuename = 0;
	u32 j;

	UNREFERENCED_PARAMETER(self);

	// Keyname Format: "HKLM\Subkey\Path\ValueName"
	for (j = 0; HKeyList[j].name; j++) {
		size_t namelen = esif_ccb_strlen(HKeyList[j].name, 30);
		if (esif_ccb_strnicmp(HKeyList[j].name, keyname, namelen) == 0 && keyname[namelen] == '\\') {
			hKey     = HKeyList[j].hkey;
			keyname += esif_ccb_strlen(HKeyList[j].name, 30) + 1;
			break;
		}
	}
	if (!hKey) {
		return rc;
	}

	regkey = esif_ccb_strdup(keyname);
	if ((valuename = strrchr(regkey, '\\')) == 0) {
		esif_ccb_free(regkey);
		return rc;
	}
	*valuename++ = 0;

	// Get Data Type from Registry if value already exists, otherwise deduce it from ESIF Data Type
	if ((dwError = RegGetValueA(hKey, regkey, valuename, dwFlags, &dwType, 0, 0)) != 0) {
		switch (value->type) {
		case ESIF_DATA_INT32:
		case ESIF_DATA_UINT32:
		case ESIF_DATA_TEMPERATURE:
			dwType = REG_DWORD;
			dwSize = value->data_len;
			break;

		case ESIF_DATA_INT64:
		case ESIF_DATA_UINT64:
			dwType = REG_QWORD;
			dwSize = value->data_len;
			break;

		case ESIF_DATA_STRING:
			dwType = REG_SZ;
			dwSize = value->data_len;
			break;

		case ESIF_DATA_BINARY:
		case ESIF_DATA_BLOB:
			dwType = REG_BINARY;
			dwSize = value->data_len;
			break;

		default:
			rc = ESIF_E_NOT_SUPPORTED;
			break;
		}
	}
	// Write Registry Value
	if (dwType != REG_NONE) {
		dwError = RegSetKeyValueA(hKey, regkey, valuename, dwType, value->buf_ptr, value->data_len);
		if (dwError == 0) {
			rc = ESIF_OK;
		}
	}
	esif_ccb_free(regkey);
	return rc;
}