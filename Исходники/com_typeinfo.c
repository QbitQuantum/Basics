/* The search string can be either:
 * a) a file name
 * b) a CLSID, major, minor e.g. "{00000200-0000-0010-8000-00AA006D2EA4},2,0"
 * c) a Type Library name e.g. "Microsoft OLE DB ActiveX Data Objects 1.0 Library"
 */
PHP_COM_DOTNET_API ITypeLib *php_com_load_typelib(char *search_string, int codepage TSRMLS_DC)
{
	ITypeLib *TL = NULL;
	char *strtok_buf, *major, *minor;
	CLSID clsid;
	OLECHAR *p;
	HRESULT hr;

	search_string = php_strtok_r(search_string, ",", &strtok_buf);

	if (search_string == NULL) {
		return NULL;
	}

	major = php_strtok_r(NULL, ",", &strtok_buf);
	minor = php_strtok_r(NULL, ",", &strtok_buf);

	p = php_com_string_to_olestring(search_string, strlen(search_string), codepage TSRMLS_CC);

	if (SUCCEEDED(CLSIDFromString(p, &clsid))) {
		WORD major_i = 1, minor_i = 0;

		/* pick up the major/minor numbers; if none specified, default to 1,0 */
		if (major && minor) {
			major_i = (WORD)atoi(major);
			minor_i = (WORD)atoi(minor);
		}

		/* Load the TypeLib by GUID */
		hr = LoadRegTypeLib((REFGUID)&clsid, major_i, minor_i, LANG_NEUTRAL, &TL);

		/* if that failed, assumed that the GUID is actually a CLSID and
		 * attemp to get the library via an instance of that class */
		if (FAILED(hr) && (major == NULL || minor == NULL)) {
			IDispatch *disp = NULL;
			ITypeInfo *info = NULL;
			int idx;

			if (SUCCEEDED(hr = CoCreateInstance(&clsid, NULL, CLSCTX_SERVER, &IID_IDispatch, (LPVOID*)&disp)) &&
					SUCCEEDED(hr = IDispatch_GetTypeInfo(disp, 0, LANG_NEUTRAL, &info))) {
				hr = ITypeInfo_GetContainingTypeLib(info, &TL, &idx);
			}

			if (info) {
				ITypeInfo_Release(info);
			}
			if (disp) {
				IDispatch_Release(disp);
			}
		}
	} else {
		/* Try to load it from a file; if it fails, do a really painful search of
		 * the registry */
		if (FAILED(LoadTypeLib(p, &TL))) {
			HKEY hkey, hsubkey;
			DWORD SubKeys, MaxSubKeyLength;
			char *keyname;
			unsigned int i, j;
			DWORD VersionCount;
			char version[20];
			char *libname;
			DWORD libnamelen;

			if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CLASSES_ROOT, "TypeLib", 0, KEY_READ, &hkey) &&
					ERROR_SUCCESS == RegQueryInfoKey(hkey, NULL, NULL, NULL, &SubKeys,
					&MaxSubKeyLength, NULL, NULL, NULL, NULL, NULL, NULL)) {

				MaxSubKeyLength++; /* make room for NUL */
				keyname = emalloc(MaxSubKeyLength);
				libname = emalloc(strlen(search_string) + 1);

				for (i = 0; i < SubKeys && TL == NULL; i++) {
					if (ERROR_SUCCESS == RegEnumKey(hkey, i, keyname, MaxSubKeyLength) &&
							ERROR_SUCCESS == RegOpenKeyEx(hkey, keyname, 0, KEY_READ, &hsubkey)) {
						if (ERROR_SUCCESS == RegQueryInfoKey(hsubkey, NULL, NULL, NULL, &VersionCount,
								NULL, NULL, NULL, NULL, NULL, NULL, NULL)) {
							for (j = 0; j < VersionCount; j++) {
								if (ERROR_SUCCESS != RegEnumKey(hsubkey, j, version, sizeof(version))) {
									continue;
								}
								/* get the default value for this key and compare */
								libnamelen = strlen(search_string)+1;
								if (ERROR_SUCCESS == RegQueryValue(hsubkey, version, libname, &libnamelen)) {
									if (0 == stricmp(libname, search_string)) {
										char *str = NULL;
										int major_tmp, minor_tmp;

										/* fetch the GUID and add the version numbers */
										if (2 != sscanf(version, "%d.%d", &major_tmp, &minor_tmp)) {
											major_tmp = 1;
											minor_tmp = 0;
										}
										spprintf(&str, 0, "%s,%d,%d", keyname, major_tmp, minor_tmp);
										/* recurse */
										TL = php_com_load_typelib(str, codepage TSRMLS_CC);

										efree(str);
										break;
									}
								}
							}
						}
						RegCloseKey(hsubkey);
					}
				}
				RegCloseKey(hkey);
				efree(keyname);
				efree(libname);
			}
		}
	}
	
	efree(p);

	return TL;
}