/////////////////////////////////////////////////////////////////////////////
// WMIInstanceProvider::modifyInstance
//
// ///////////////////////////////////////////////////////////////////////////
void WMIInstanceProvider::modifyInstance(
    const String& nameSpace,
    const String& userName,
    const String& password,
    const CIMInstance& modifiedInstance,
    Boolean includeQualifiers,
    const CIMPropertyList& propertylist)
{
    PEG_METHOD_ENTER(TRC_WMIPROVIDER,"WMIClassProvider::modifyInstance()");

    HRESULT hr;
    CComPtr<IWbemClassObject> pClass;
    CComPtr<IWbemClassObject> pInstance;

    setup(nameSpace, userName, password);

    PEG_TRACE((TRC_WMIPROVIDER,
                  Tracer::LEVEL3,
                  "ModifyInstance() - nameSpace %s, userName %s",
                  nameSpace.getCString(),
                  userName.getCString()));

    if (!m_bInitialized)
    {
        PEG_TRACE((TRC_WMIPROVIDER, Tracer::LEVEL1,
            "WMIInstanceProvider::ModifyInstance - m_bInitilized= %x, "
            "throw CIM_ERR_FAILED exception",
            m_bInitialized));

        throw CIMException(CIM_ERR_FAILED);
    }

    // Check if the instance's class is valid.
    String className = modifiedInstance.getClassName().getString();

    if (!(_collector->getObject(&pClass, className)))
    {
        if (pClass)
            pClass.Release();

        throw CIMException(CIM_ERR_INVALID_CLASS);
    }
    else if (_collector->isInstance(pClass))
    {
        if (pClass)
            pClass.Release();

        throw CIMException(CIM_ERR_INVALID_PARAMETER);
    }

    if (pClass)
        pClass.Release();

    // Get the instance path
    CIMObjectPath objPath = modifiedInstance.getPath();

    // Get the name of the instance
    String instanceName = getObjectName(objPath);

    // Check if the instance exists
    if (!(_collector->getObject(&pInstance, instanceName)))
    {
        if (pInstance)
            pInstance.Release();

        throw CIMException(CIM_ERR_NOT_FOUND);
    }
    else if (!(_collector->isInstance(pInstance)))
    {
        if (pInstance)
            pInstance.Release();

        throw CIMException(CIM_ERR_INVALID_PARAMETER);
    }

    // Set the properties that are into propertylist
    Array<CIMName> listNames;
    listNames = propertylist.getPropertyNameArray();

    bool foundInArray;
    bool bPropertySet = false;

    for(Uint32 i = 0; i < modifiedInstance.getPropertyCount(); i++)
    {
        CComVariant v;
        CIMProperty property = modifiedInstance.getProperty(i).clone();
        String sPropName = property.getName().getString();

        // change only the properties defined into the array
        // if the array is null, change all properties
        if (propertylist.isNull())
        {
            foundInArray = true;
        }
        else
        {
            foundInArray = false;
            for (Uint32 j = 0; (j < listNames.size()) && !foundInArray; j++)
                //if (listNames[j].getString() == str)
                if (String::equalNoCase(listNames[j].getString(), sPropName))
                    foundInArray = true;
        }

        if (foundInArray)
        {
            WMIValue propertyValue = property.getValue();

            try
            {
                propertyValue.getAsVariant(&v,nameSpace, userName, password);
            }
            catch (CIMException&)
            {
                if (pInstance)
                    pInstance.Release();

                v.Clear();

                throw;
            }

            CComBSTR bs = sPropName.getCString();
            hr = pInstance->Put(bs, 0, &v, 0);
            v.Clear();

            // If we fail to set one property, we must assure
            // that the others will be processed
            if(SUCCEEDED(hr))
            {
                // Mark that at least one property was set
                bPropertySet = true;
            }
        }
    }

    // Check if at least one property was set
    // otherwise throw invalid parameter error
    if(!bPropertySet)
    {
        PEG_TRACE((TRC_WMIPROVIDER,
                      Tracer::LEVEL1,
                      "modifyInstance() - Put Failed hr=0x%x.",
                      hr));

        throw CIMException(CIM_ERR_FAILED);
    }

    // Connect to the server
    CComPtr<IWbemServices> pServices;
    bool bConnected = _collector->Connect(&pServices);

    if (!bConnected)
    {
        throw CIMException(CIM_ERR_ACCESS_DENIED);
    }

    // Write the instance to WMI.
    hr = pServices->PutInstance(pInstance,
                                WBEM_FLAG_UPDATE_ONLY,
                                NULL,
                                NULL);

    if (pInstance)
        pInstance.Release();

    if (pServices)
        pServices.Release();

    if(FAILED(hr))
    {
        switch(hr)
        {
            case E_ACCESSDENIED:
                throw CIMException(CIM_ERR_ACCESS_DENIED);
                break;
            case WBEM_E_ACCESS_DENIED:
                throw CIMException(CIM_ERR_ACCESS_DENIED);
                break;
            case WBEM_E_NOT_FOUND:
                throw CIMException(CIM_ERR_NOT_FOUND);
                break;
            case WBEM_E_INVALID_CLASS:
                throw CIMException(CIM_ERR_INVALID_CLASS);
                break;
            case WBEM_E_INVALID_OBJECT:
                throw CIMException(CIM_ERR_INVALID_PARAMETER);
                break;
            default:
                throw CIMException(CIM_ERR_FAILED);
        }
    }

    PEG_METHOD_EXIT();

    return;
}