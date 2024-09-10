/******************************************************************************
 *                                                                            *
 * Function: zbx_wmi_get                                                      *
 *                                                                            *
 * Purpose: wrapper function for zbx_wmi_get_variant(), stores the retrieved  *
 *          WMI value as UTF-8 encoded string                                 *
 *                                                                            *
 * Parameters: wmi_namespace [IN]  - object path of the WMI namespace (UTF-8) *
 *             wmi_query     [IN]  - WQL query (UTF-8)                        *
 *             utf8_value    [OUT] - address of the pointer to the retrieved  *
 *                                   value (dynamically allocated)            *
 *                                                                            *
 * Comments: if either retrieval or type conversion failed then *utf8_value   *
 *           remains unchanged (set it to NULL before calling this function   *
 *           to check for this condition). Callers must free *utf8_value.     *
 *                                                                            *
 ******************************************************************************/
extern "C" void	zbx_wmi_get(const char *wmi_namespace, const char *wmi_query, char **utf8_value)
{
	VARIANT		vtProp;
	HRESULT		hres;

	VariantInit(&vtProp);

	if (SUCCEED != zbx_co_initialize())
	{
		zabbix_log(LOG_LEVEL_DEBUG, "cannot initialize COM library for querying WMI");
		goto out;
	}

	if (SYSINFO_RET_FAIL == zbx_wmi_get_variant(wmi_namespace, wmi_query, &vtProp))
	{
		zabbix_log(LOG_LEVEL_DEBUG, "cannot get WMI result");
		goto out;
	}

	hres = VariantChangeType(&vtProp, &vtProp, VARIANT_ALPHABOOL, VT_BSTR);

	if (FAILED(hres))
	{
		zabbix_log(LOG_LEVEL_DEBUG, "cannot convert WMI result of type %d to VT_BSTR", vtProp.vt);
		goto out;
	}

	*utf8_value = zbx_unicode_to_utf8((wchar_t *)_bstr_t(vtProp.bstrVal));
out:
	VariantClear(&vtProp);
}