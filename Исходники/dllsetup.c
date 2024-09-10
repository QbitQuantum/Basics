/****************************************************************************
 * SetupRegisterServers
 *
 * This function is table driven using the static members of the
 * CFactoryTemplate class defined in the Dll.
 *
 * It registers the Dll as the InprocServer32 for all the classes in
 * CFactoryTemplate
 *
 ****************************************************************************/
HRESULT SetupRegisterServers(const CFactoryTemplate * pList, int num,
                             BOOL bRegister)
{
    static const WCHAR szFileName[] = {'q','c','a','p','.','d','l','l',0};
    HRESULT hr = NOERROR;
    IFilterMapper2 *pIFM2 = NULL;
    IFilterMapper *pIFM = NULL;

    /* first register all server classes, just to make sure */
    if (bRegister)
        hr = SetupRegisterAllClasses(pList, num, szFileName, TRUE );

    /* next, register/unregister all filters */
    if (SUCCEEDED(hr))
    {
        hr = CoInitialize(NULL);

        TRACE("Getting IFilterMapper2\r\n");
        hr = CoCreateInstance(&CLSID_FilterMapper2, NULL, CLSCTX_INPROC_SERVER,
                              &IID_IFilterMapper2, (void **)&pIFM2);
        if (FAILED(hr))
        {
            TRACE("- trying IFilterMapper instead\r\n");

            hr = CoCreateInstance(&CLSID_FilterMapper, NULL, CLSCTX_INPROC_SERVER,
                                  &IID_IFilterMapper, (void **)&pIFM);
        }

        if (SUCCEEDED(hr))
        {
            int i;
            
            /* scan through array of CFactoryTemplates registering all filters */
            for (i = 0; i < num; i++, pList++)
            {
                if (NULL != pList->m_pAMovieSetup_Filter)
                {
                    if (pIFM2)
                        hr = SetupRegisterFilter2(pList->m_pAMovieSetup_Filter,
                                                  pIFM2, bRegister);
                    else
                        hr = SetupRegisterFilter(pList->m_pAMovieSetup_Filter,
                                                 pIFM, bRegister);
                }

                /* check final error for this pass and break loop if we failed */
                if (FAILED(hr))
                    break;
            }

            /* release interface */
            if (pIFM2)
                IFilterMapper2_Release(pIFM2);
            else
                IFilterMapper_Release(pIFM);
        }

        /* and clear up */
        CoFreeUnusedLibraries();
        CoUninitialize();
    }

    /* if unregistering, unregister all OLE servers */
    if (SUCCEEDED(hr) && !bRegister)
        hr = SetupRegisterAllClasses(pList, num, szFileName, FALSE);
    return hr;
}