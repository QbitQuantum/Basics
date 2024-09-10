// Writes properties on the user specified object.
void WriteContentProperties(
    IPortableDevice*    pDevice)
{
    if (pDevice == NULL)
    {
        printf("! A NULL IPortableDevice interface pointer was received\n");
        return;
    }
	//<SnippetContentProp3>
    HRESULT                               hr                   = S_OK;
    WCHAR                                 szSelection[81]      = {0};
    WCHAR                                 szNewObjectName[81]  = {0};
    CComPtr<IPortableDeviceProperties>    pProperties;
    CComPtr<IPortableDeviceContent>       pContent;
    CComPtr<IPortableDeviceValues>        pObjectPropertiesToWrite;
    CComPtr<IPortableDeviceValues>        pPropertyWriteResults;
    CComPtr<IPortableDeviceValues>        pAttributes;
    BOOL                                  bCanWrite            = FALSE;

    // Prompt user to enter an object identifier on the device to write properties on.
    printf("Enter the identifer of the object you wish to write properties on.\n>");
    hr = StringCbGetsW(szSelection,sizeof(szSelection));
    if (FAILED(hr))
    {
        printf("An invalid object identifier was specified, aborting property reading\n");
    }
	//</SnippetContentProp3>
    // 1) Get an IPortableDeviceContent interface from the IPortableDevice interface to
    // access the content-specific methods.
	//<SnippetContentProp4>
    if (SUCCEEDED(hr))
    {
        hr = pDevice->Content(&pContent);
        if (FAILED(hr))
        {
            printf("! Failed to get IPortableDeviceContent from IPortableDevice, hr = 0x%lx\n",hr);
        }
    }

    // 2) Get an IPortableDeviceProperties interface from the IPortableDeviceContent interface
    // to access the property-specific methods.
    if (SUCCEEDED(hr))
    {
        hr = pContent->Properties(&pProperties);
        if (FAILED(hr))
        {
            printf("! Failed to get IPortableDeviceProperties from IPortableDevice, hr = 0x%lx\n",hr);
        }
    }

    // 3) Check the property attributes to see if we can write/change the WPD_OBJECT_NAME property.
    if (SUCCEEDED(hr))
    {
        hr = pProperties->GetPropertyAttributes(szSelection,
                                                WPD_OBJECT_NAME,
                                                &pAttributes);
        if (SUCCEEDED(hr))
        {
            hr = pAttributes->GetBoolValue(WPD_PROPERTY_ATTRIBUTE_CAN_WRITE, &bCanWrite);
            if (SUCCEEDED(hr))
            {
                if (bCanWrite)
                {
                    printf("The attribute WPD_PROPERTY_ATTRIBUTE_CAN_WRITE for the WPD_OBJECT_NAME reports TRUE\nThis means that the property can be changed/updated\n\n");
                }
                else
                {
                    printf("The attribute WPD_PROPERTY_ATTRIBUTE_CAN_WRITE for the WPD_OBJECT_NAME reports FALSE\nThis means that the property cannot be changed/updated\n\n");
                }
            }
            else
            {
                printf("! Failed to get the WPD_PROPERTY_ATTRIBUTE_CAN_WRITE value from WPD_OBJECT_NAME on object '%ws', hr = 0x%lx\n",szSelection, hr);
            }
        }
    }
	//</SnippetContentProp4>

    // 4) Prompt the user for the new value of the WPD_OBJECT_NAME property only if the property attributes report
    // that it can be changed/updated.
	//<SnippetContentProp5>
    if (bCanWrite)
    {
        printf("Enter the new WPD_OBJECT_NAME for the object '%ws'.\n>",szSelection);
        hr = StringCbGetsW(szNewObjectName,sizeof(szNewObjectName));
        if (FAILED(hr))
        {
            printf("An invalid object name was specified, aborting property writing\n");
        }

        // 5) CoCreate an IPortableDeviceValues interface to hold the the property values
        // we wish to write.
        if (SUCCEEDED(hr))
        {
            hr = CoCreateInstance(CLSID_PortableDeviceValues,
                                  NULL,
                                  CLSCTX_INPROC_SERVER,
                                  IID_PPV_ARGS(&pObjectPropertiesToWrite));
            if (SUCCEEDED(hr))
            {
                if (pObjectPropertiesToWrite != NULL)
                {
                    hr = pObjectPropertiesToWrite->SetStringValue(WPD_OBJECT_NAME, szNewObjectName);
                    if (FAILED(hr))
                    {
                        printf("! Failed to add WPD_OBJECT_NAME to IPortableDeviceValues, hr= 0x%lx\n", hr);
                    }
                }
            }
        }
		//</SnippetContentProp5>
        // 6) Call SetValues() passing the collection of specified PROPERTYKEYs.
		//<SnippetContentProp6>
        if (SUCCEEDED(hr))
        {
            hr = pProperties->SetValues(szSelection,                // The object whose properties we are reading
                                        pObjectPropertiesToWrite,   // The properties we want to read
                                        &pPropertyWriteResults);    // Driver supplied property result values for the property read operation
            if (FAILED(hr))
            {
                printf("! Failed to set properties for object '%ws', hr= 0x%lx\n", szSelection, hr);
            }
            else
            {
                printf("The WPD_OBJECT_NAME property on object '%ws' was written successfully (Read the properties again to see the updated value)\n", szSelection);
            }
        }
		//</SnippetContentProp6>
    }
}