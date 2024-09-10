HRESULT CModuleConfiguration::GetString(IAppHostElement* section, LPCWSTR propertyName, LPWSTR* value)
{
	HRESULT hr = S_OK;
    BSTR sysPropertyName = NULL;
    BSTR sysPropertyValue = NULL;
    IAppHostProperty* prop = NULL;

	CheckNull(value);
	*value = NULL;
	ErrorIf(NULL == (sysPropertyName = SysAllocString(propertyName)), ERROR_NOT_ENOUGH_MEMORY);
	CheckError(section->GetPropertyByName(sysPropertyName, &prop));
	CheckError(prop->get_StringValue(&sysPropertyValue));
	ErrorIf(NULL == (*value = new WCHAR[wcslen(sysPropertyValue) + 1]), ERROR_NOT_ENOUGH_MEMORY);
	wcscpy(*value, sysPropertyValue);

Error:

    if ( sysPropertyName )
    {
        SysFreeString(sysPropertyName);
        sysPropertyName = NULL;
    }

    if ( sysPropertyValue )
    {
        SysFreeString(sysPropertyValue);
        sysPropertyValue = NULL;
    }

    if (prop)
    {
        prop->Release();
        prop = NULL;
    }

    return hr;
}