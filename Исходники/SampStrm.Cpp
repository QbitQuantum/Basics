HRESULT CSampleMSPStream::FireEvent(
    IN MSP_CALL_EVENT        type,
    IN HRESULT               hrError,
    IN MSP_CALL_EVENT_CAUSE  cause
    )                                          
{
    LOG((MSP_EVENT, "CSampleMSPStream::FireEvent - enter"));

    //
    // Create the event structure. 
    //

    //
    // Note: 
    //
    // MSPEVENTITEMs are allocated with AllocateEventItem and freed with 
    // FreeEventItem
    //
    // AllocateEventItem takes an optional argument that specifies how many 
    // extra bytes need to be allocated in addition to the size of MSPEVENTITEM
    // 

    MSPEVENTITEM * pEventItem = AllocateEventItem();

    if (pEventItem == NULL)
    {
        LOG((MSP_ERROR, "CSampleMSPStream::FireEvent - "
            "can't create MSPEVENTITEM structure - exit E_OUTOFMEMORY"));

        return E_OUTOFMEMORY;
    }

    //
    // Fill in the necessary fields for the event structure.
    //

    pEventItem->MSPEventInfo.dwSize = sizeof(MSP_EVENT_INFO);
    pEventItem->MSPEventInfo.Event  = ME_CALL_EVENT;

    ITTerminal * pTerminal = NULL;

    if ( 0 != m_Terminals.GetSize() )
    {
        _ASSERTE( 1 == m_Terminals.GetSize() );
        pTerminal = m_Terminals[0];
        pTerminal->AddRef();
    }

    ITStream * pStream = (ITStream *) this;
    pStream->AddRef();

    pEventItem->MSPEventInfo.MSP_CALL_EVENT_INFO.Type      = type;
    pEventItem->MSPEventInfo.MSP_CALL_EVENT_INFO.Cause     = cause;
    pEventItem->MSPEventInfo.MSP_CALL_EVENT_INFO.pStream   = pStream;
    pEventItem->MSPEventInfo.MSP_CALL_EVENT_INFO.pTerminal = pTerminal;
    pEventItem->MSPEventInfo.MSP_CALL_EVENT_INFO.hrError   = hrError;


#ifdef MSPLOG
    //
    // Spew some debug output to indicate what this is.
    //

    char * pszType;
    DWORD dwLevel;

    switch (type)
    {
    case CALL_NEW_STREAM:
        pszType = "CALL_NEW_STREAM (unexpected)";
        dwLevel = MSP_ERROR;
        break;

    case CALL_STREAM_FAIL:
        pszType = "CALL_STREAM_FAIL";
        dwLevel = MSP_INFO;
        break;

    case CALL_TERMINAL_FAIL:
        pszType = "CALL_TERMINAL_FAIL";
        dwLevel = MSP_INFO;
        break;

    case CALL_STREAM_NOT_USED:
        pszType = "CALL_STREAM_NOT_USED (unexpected)";
        dwLevel = MSP_ERROR;
        break;

    case CALL_STREAM_ACTIVE:
        pszType = "CALL_STREAM_ACTIVE";
        dwLevel = MSP_INFO;
        break;

    case CALL_STREAM_INACTIVE:
        pszType = "CALL_STREAM_INACTIVE";
        dwLevel = MSP_INFO;
        break;

    default:
        pszType = "UNKNOWN EVENT TYPE";
        dwLevel = MSP_ERROR;
        break;
    }

    LOG((dwLevel, "CSampleMSPStream::FireEvent - "
                  "EVENT DUMP: type      = %s", pszType));
    LOG((dwLevel, "CSampleMSPStream::FireEvent - "
                  "EVENT DUMP: pStream   = %p", pStream));    
    LOG((dwLevel, "CSampleMSPStream::FireEvent - "
                  "EVENT DUMP: pTerminal = %p", pTerminal));    
    LOG((dwLevel, "CSampleMSPStream::FireEvent - "
                  "EVENT DUMP: hrError   = %08x", hrError));    

#endif // ifdef MSPLOG

    //
    // Send the event to the app.
    //

    HRESULT hr = m_pMSPCall->HandleStreamEvent(pEventItem);

    if (FAILED(hr))
    {
        LOG((MSP_ERROR, "CSampleMSPStream::FireEvent - "
            "HandleStreamEvent failed - returning 0x%08x", hr));

        pStream->Release();
        pTerminal->Release();

        
        //
        // Note:
        //
        // MSPEVENTITEMs are allocated with AllocateEventItem and freed with 
        // FreeEventItem
        //

        FreeEventItem(pEventItem);
        pEventItem = NULL;

        return hr;
    }

    LOG((MSP_EVENT, "CSampleMSPStream::FireEvent - exit S_OK"));

    return S_OK;
}