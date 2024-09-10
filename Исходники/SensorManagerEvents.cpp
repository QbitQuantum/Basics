///////////////////////////////////////////////////////////////////////////////
//
// CSensorManagerEvents::GetSensorProperty
//
// Description of function/method:
//        Retrieves sensor properties to be stored for future reference
//
// Parameters:
//        SENSOR_ID SensorID:	Unique ID for sensor used as Key to std::MAP 
//		  ISensor* pSensor:		Sensor to be queried 
//		  REFPROPERTYKEY pk:	Property to be set, currently only Name is stored
//
// Return Values:
//        S_OK on success, else an error
//
///////////////////////////////////////////////////////////////////////////////
HRESULT CSensorManagerEvents::GetSensorProperty(SENSOR_ID SensorID, ISensor* pSensor, REFPROPERTYKEY pk)
{

    HRESULT hr = S_OK;

    PROPVARIANT pv = {};
    hr = pSensor->GetProperty(pk, &pv);

    if(SUCCEEDED(hr))
    {
        if(pv.vt == VT_UI4)  // Number
        {
            wprintf_s(L"\nSensor integer value: %u\n", pv.ulVal);
        }
        else if(pv.vt == VT_LPWSTR)  // String
        {
			if(pk == SENSOR_PROPERTY_FRIENDLY_NAME)
			{
				int size = (int)wcslen(pv.pwszVal)+1;
				m_Properties[SensorID].m_Name = (WCHAR*)malloc(size*sizeof(WCHAR));
				wsprintf(m_Properties[SensorID].m_Name,L"%s",pv.pwszVal);
			}
        }
        else  // Interface or vector
        {
            wprintf_s(L"\nSensor property is a compound type. Unable to print value.");
        }
    }

    PropVariantClear(&pv);
    return hr;    
}