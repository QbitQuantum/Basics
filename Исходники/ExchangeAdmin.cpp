HRESULT ExchangeAdmin::GetAllProfiles(vector<string> &vProfileList)
{
    HRESULT hr = S_OK;
    Zimbra::Util::ScopedInterface<IMAPITable> pProftable;

    // get profile table
    if ((hr = m_pProfAdmin->GetProfileTable(0, pProftable.getptr())) == S_OK)
    {
        SizedSPropTagArray(3, proftablecols) = {
            3, { PR_DISPLAY_NAME_A, PR_DEFAULT_PROFILE, PR_SERVICE_NAME }
        };

        Zimbra::Util::ScopedRowSet profrows;

        // get all profile rows
        if ((hr = HrQueryAllRows(pProftable.get(), (SPropTagArray *)&proftablecols, NULL, NULL,
                0, profrows.getptr())) == S_OK)
        {
            for (unsigned int i = 0; i < profrows->cRows; i++)
            {
                if (profrows->aRow[i].lpProps[0].ulPropTag == PR_DISPLAY_NAME_A)
                {
                    Zimbra::Util::ScopedInterface<IMsgServiceAdmin> spServiceAdmin;
                    Zimbra::Util::ScopedInterface<IMAPITable> spServiceTable;
                    string strpname = profrows->aRow[i].lpProps[0].Value.lpszA;

                    // get profile's admin service
                    hr = m_pProfAdmin->AdminServices((LPTSTR)strpname.c_str(), NULL, NULL, 0,
                        spServiceAdmin.getptr());
                    if (FAILED(hr))
                        throw ExchangeAdminException(hr,L"GetAllProfiles(): AdminServices Failed.",
						ERR_GETALL_PROFILE, __LINE__, __FILE__);
                    // get message service table
                    hr = spServiceAdmin->GetMsgServiceTable(0, spServiceTable.getptr());
                    if (FAILED(hr))
                    {
                        throw ExchangeAdminException(hr,L"GetAllProfiles(): GetMsgServiceTable Failed.",
							ERR_GETALL_PROFILE, __LINE__, __FILE__);
                    }
                    // lets get the service name and the service uid for the primary service
                    SizedSPropTagArray(2, tags) = {
                        2, { PR_SERVICE_NAME, PR_SERVICE_UID }
                    };
                    spServiceTable->SetColumns((LPSPropTagArray) & tags, 0);

                    DWORD dwCount = 0;

                    hr = spServiceTable->GetRowCount(0, &dwCount);
                    if (FAILED(hr))
                        throw ExchangeAdminException(hr,
                            L"GetAllProfiles(): GetRowCount Failed.",
							ERR_GETALL_PROFILE, __LINE__, __FILE__);
                    else if (!dwCount)
                        return hr;

                    Zimbra::Util::ScopedRowSet pRows;

                    hr = spServiceTable->QueryRows(dwCount, 0, pRows.getptr());
                    if (FAILED(hr))
                        throw ExchangeAdminException(hr, L"GetAllProfiles(): QueryRows Failed.",
                            ERR_GETALL_PROFILE, __LINE__, __FILE__);
                    for (ULONG j = 0; j < pRows->cRows; j++)
                    {
                        if (PR_SERVICE_NAME == pRows->aRow[j].lpProps[0].ulPropTag)
                        {
                            // if MSExchange service
                            if (0 == lstrcmpiW(pRows->aRow[j].lpProps[0].Value.LPSZ, L"MSEMS"))
                            {
                                if (profrows->aRow[i].lpProps[0].ulPropTag == PR_DISPLAY_NAME_A)
                                    vProfileList.push_back(
                                        profrows->aRow[i].lpProps[0].Value.lpszA);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return hr;
}