STDMETHODIMP CLocationReport::GetValue(REFPROPERTYKEY pKey, PROPVARIANT *pValue)
{
    HRESULT hr = S_OK;

    // properties for civic address reports
    if (pKey.pid == SENSOR_DATA_TYPE_ADDRESS1.pid)
    {
        hr = InitPropVariantFromString(m_address1, pValue);
    } 
    else if (pKey.pid == SENSOR_DATA_TYPE_ADDRESS2.pid)
    {    
        hr = InitPropVariantFromString(m_address2, pValue);
    }
    else if (pKey.pid == SENSOR_DATA_TYPE_CITY.pid)
    {
        hr = InitPropVariantFromString(m_city, pValue);
    }
    else if (pKey.pid == SENSOR_DATA_TYPE_STATE_PROVINCE.pid)
    {
        hr = InitPropVariantFromString(m_stateprovince, pValue);
    } 
    else if (pKey.pid == SENSOR_DATA_TYPE_POSTALCODE.pid)
    {
        hr = InitPropVariantFromString(m_postalcode, pValue);
    }
    else if (pKey.pid == SENSOR_DATA_TYPE_COUNTRY_REGION.pid)    
    {
        hr = InitPropVariantFromString(m_countryregion, pValue);
    }
    // properties for latitude/longitude reports
    else if (pKey.pid == SENSOR_DATA_TYPE_LATITUDE_DEGREES.pid)
    {
        hr = InitPropVariantFromDouble(m_latitude, pValue);
    } 
    else if (pKey.pid == SENSOR_DATA_TYPE_LONGITUDE_DEGREES.pid)
    {
        hr = InitPropVariantFromDouble(m_longitude, pValue);
    }
    else if (pKey.pid == SENSOR_DATA_TYPE_ERROR_RADIUS_METERS.pid)    
    {
        hr = InitPropVariantFromDouble(m_errorradius, pValue);
    }
    else 
    {
        hr = HRESULT_FROM_WIN32(ERROR_NO_DATA);
        PropVariantInit(pValue);
    }

    return hr;
}