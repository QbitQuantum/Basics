HRESULT STDMETHODCALLTYPE
CStockQuoteProxy::EndGetLastTradePrice
(   /* [in] */ IWSDAsyncResult* AsyncResult
               ,   /* [out] */ TRADE_PRICE** bodyOut
)
{
    WSD_EVENT ev;
    HRESULT hr = S_OK;


    // Initialize Output Pointers
    if( NULL != bodyOut )
    {
        *bodyOut = NULL;
    }
    if( NULL == AsyncResult )
    {
        hr = E_INVALIDARG;
        return hr;
    }

    // Validate Response Parameters
    if( NULL == bodyOut )
    {
        hr = E_POINTER;
        return hr;
    }

    ::ZeroMemory(&ev, sizeof(ev));
    hr = AsyncResult->GetEvent( &ev );
    if( S_OK != hr )
    {
        return hr;
    }

    if( ev.EventType == WSDET_INCOMING_MESSAGE )
    {
        void* results = ev.Soap->Body;
        if( NULL != results )
        {
            RESPONSEBODY_StockQuotePortType_GetLastTradePrice* response = reinterpret_cast<RESPONSEBODY_StockQuotePortType_GetLastTradePrice*>(results);

            WSDDetachLinkedMemory( (void*) response->body );
            *bodyOut = response->body;

            WSDFreeLinkedMemory( (void*) response );
        }
    }
    else if( ev.EventType == WSDET_INCOMING_FAULT )
    {
        void* results = ev.Soap->Body;

        if( NULL == m_genericProxy )
        {
            hr = E_ABORT;
            return hr;
        }

        IWSDEndpointProxy* ep = NULL;
        hr = m_genericProxy->GetEndpointProxy(&ep);
        if( FAILED(hr) || NULL == ep )
        {
            hr = E_ABORT;
            return hr;
        }

        hr = E_FAIL;
        if( results )
        {
            ep->ProcessFault( (const WSD_SOAP_FAULT*)results );
        }
        ep->Release();
    }
    else
    {
        hr = ( (S_OK == ev.Hr) ? E_FAIL : ev.Hr );
    }

    return hr;
}