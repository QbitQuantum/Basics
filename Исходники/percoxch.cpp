/**
 * Gets identifiers map.
 *
 * Parameters:
 * None.
 *
 * Returns:
 * Identifiers map.
 */
perco_exchange::ids_t perco_exchange::getIdentifiers()
{
    ids_t ids;
    logger::const_ptr_t pLogger = logger::getInstance();
    ATL::CComPtr<PERCo_S20_SDK::IExchangeMain> percoXchg;
    if (SUCCEEDED(percoXchg.CoCreateInstance(__uuidof(PERCo_S20_SDK::CoExchangeMain))))
    {
        if (SUCCEEDED(percoXchg->SetConnect(PERCO_HOST, PERCO_PORT, PERCO_LOGIN, PERCO_PWD)))
        {
            BSTR szDBVersion;
            BSTR szSDKVersion;
            if (!percoXchg->CheckVersion(&szDBVersion, &szSDKVersion))
            {
                ATL::CComPtr<IXMLDOMDocument2> request = getStaffRequest();
#pragma region log
                pLogger->logNotify(logger::CategoryGeneral, IDS_EVENT_STAFF_REQUEST_SEND);
                AtlTrace2(ATL::atlTraceGeneral, 0, "Sending the 'staff' request.\r\n");
#pragma endregion log the message
                if (request && SUCCEEDED(percoXchg->GetData(request)))
                {
#pragma region log
                    pLogger->logNotify(logger::CategoryGeneral, IDS_EVENT_STAFF_REQUEST_HANDLED);
                    AtlTrace2(ATL::atlTraceGeneral, 0, "PERCo has responded to the 'staff' request.\r\n");
#pragma endregion log the message
                    ids = parseStaffResponse(request);
#pragma region log
                    CStringUtil::const_ptr_t pStringUtil = CStringUtil::getInstance();
                    LPTSTR pszFormat;
                    size_t nLength;
                    if (CStringUtil::ResourceSuccess ==
                        pStringUtil->loadString(IDS_EVENT_T_RESPOND_SIZE, &pszFormat, &nLength))
                    {
                        const STLADD regex_type regex(TEXT("(?:[^%]*)(?:%[[:digit:]]{0,2}u){1,1}(?:[^%]*)"));
                        if (std::regex_match(pszFormat, pszFormat + nLength, regex))
                        {
                            nLength += 15;
                            CMemoryManager::pointer_t pMemoryManager = CMemoryManager::getInstance();
                            LPTSTR pszText = pMemoryManager->mAllocChars<LPTSTR>(nLength);
                            if (pszText)
                            {
                                nLength = _stprintf_s(pszText, nLength, pszFormat, ids.size());
                                pLogger->log(logger::CategoryGeneral, logger::SeverityNotify, pszText, nLength);
                                pMemoryManager->free(pszText);
                            }
                        }
                        pStringUtil->freeString(pszFormat);
                    }
                    AtlTrace2(ATL::atlTraceGeneral, 0, "The respond parsed (%u entries handled).\r\n", ids.size());
#pragma endregion log the message
                }
            }
            percoXchg->DisConnect();
        }
    }
    else
    {
#pragma region log
        pLogger->logError(logger::CategoryCOM, IDS_EVENT_IEXCHANGEMAIN_AINT_REGISTERED);
        AtlTrace2(ATL::atlTraceCOM, 0, "'PERCo_S20_SDK::IExchangeMain' ain't registered.\r\n");
#pragma endregion log the message
    }
    return ids;
}