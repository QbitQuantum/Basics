HRESULT CWIAPropertyManager::SetItemProperties(__inout BYTE *pWiasContext)
{

    HRESULT hr = E_INVALIDARG;
    if(pWiasContext)
    {
        hr = S_OK;

        //
        // get current number of properties in the list
        //

        LONG lNumProps = m_List.Size();
        if(lNumProps)
        {
            LONG lIndex = 0;

            LPOLESTR *pszName = (LPOLESTR*) LocalAlloc(LPTR,sizeof(LPOLESTR)*lNumProps);
            PROPID *ppid = (PROPID*) LocalAlloc(LPTR,sizeof(PROPID)*lNumProps);
            PROPVARIANT *ppv = (PROPVARIANT*) LocalAlloc(LPTR,sizeof(PROPVARIANT)*lNumProps);
            PROPSPEC *pps = (PROPSPEC*) LocalAlloc(LPTR,sizeof(PROPSPEC)*lNumProps);
            WIA_PROPERTY_INFO *pwpi = (WIA_PROPERTY_INFO*) LocalAlloc(LPTR,sizeof(WIA_PROPERTY_INFO)*lNumProps);

            if((pszName)&&(ppid)&&(ppv)&&(pps)&&(pwpi))
            {

                //
                // copy the property data into the proper structures
                //

                for(INT i = 0; i < m_List.Size(); i++)
                {
                    PWIA_PROPERTY_INFO_DATA pPropertyData = m_List[i];
                    if(pPropertyData)
                    {
                        pszName[lIndex] = pPropertyData->szName;
                        ppid[lIndex] = pPropertyData->pid;
                        memcpy(&ppv[lIndex],&pPropertyData->pv,sizeof(PROPVARIANT));
                        memcpy(&pps[lIndex],&pPropertyData->ps, sizeof(PROPSPEC));
                        memcpy(&pwpi[lIndex],&pPropertyData->wpi,sizeof(WIA_PROPERTY_INFO));
                        lIndex++;
                    }
                }

                //
                // send the property names to the WIA service
                //

                hr = wiasSetItemPropNames(pWiasContext,lNumProps,ppid,pszName);
                if(SUCCEEDED(hr))
                {

                    //
                    // send the property values to the WIA service
                    //

                    hr = wiasWriteMultiple(pWiasContext,lNumProps,pps,ppv);
                    if(SUCCEEDED(hr))
                    {

                        //
                        // send the property valid values to the WIA service
                        //

                        hr = wiasSetItemPropAttribs(pWiasContext,lNumProps,pps,pwpi);
                        if(FAILED(hr))
                        {
                            WIAS_ERROR((g_hInst, "CWIAPropertyManager_SetItemProperties - wiasSetItemPropAttribs failed"));
                        }
                    }
                    else
                    {
                        WIAS_ERROR((g_hInst, "CWIAPropertyManager_SetItemProperties - wiasWriteMultiple failed"));
                    }
                }
                else
                {
                    WIAS_ERROR((g_hInst, "CWIAPropertyManager_SetItemProperties - wiasSetItemPropNames failed"));
                }
            }
            else
            {
                WIAS_ERROR((g_hInst, "CWIAPropertyManager_SetItemProperties - failed to allocate memory for property arrays"));
                hr = E_OUTOFMEMORY;
            }

            //
            // always delete any temporary memory allocated before exiting the function.  The WIA
            // service makes a copy of the information during the "wias" helper calls.
            //

            if(pszName)
            {
                LocalFree(pszName);
                pszName = NULL;
            }

            if(ppid)
            {
                LocalFree(ppid);
                ppid = NULL;
            }

            if(ppv)
            {
                LocalFree(ppv);
                ppv = NULL;
            }

            if(pps)
            {
                LocalFree(pps);
                pps = NULL;
            }

            if(pwpi)
            {
                LocalFree(pwpi);
                pwpi = NULL;
            }
        }
    }
    return hr;
}