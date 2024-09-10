//////////////////////////////////////////////////////////////////////////////
// CStockQuoteService::GetLastTradePrice
//  Service method which can be called by remote clients.  This method
//  takes the stock quote listed in the parameters structure and returns
//  a structure with a stock price.
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CStockQuoteService::GetLastTradePrice(
    TRADE_PRICE_REQUEST* parameters, 
    TRADE_PRICE** ppTradePrice)
{
    TRADE_PRICE* pTradePrice = NULL;
    HRESULT hr = S_OK;

    _cwprintf(L"Client invoking GetLastTradePrice method\r\n");

    // Validate parameters
    if( NULL == parameters )
    {
        return E_INVALIDARG;
    }

    if( NULL == parameters->tickerSymbol )
    {
        return E_INVALIDARG;
    }

    if( NULL == ppTradePrice )
    {
        return E_POINTER;
    }

    *ppTradePrice = NULL;

    // Allocate response structure with WSDAllocateLinkedMemory.  The
    // Deallocator for this port type's stub functions is WSDFreeLinkedMemory.
    _cwprintf(L"    Allocating response structure... ");
    pTradePrice = (TRADE_PRICE*)WSDAllocateLinkedMemory( NULL,
            sizeof(TRADE_PRICE) );

    if( NULL == pTradePrice )
    {
        hr = E_OUTOFMEMORY;
    }

    print_result( hr );

    // Fill response structure
    if( S_OK == hr )
    {
        _cwprintf(L"    Calling into StockLookup function... ");
        pTradePrice->price = StockLookup(parameters->tickerSymbol);
        print_result( hr );
    }

    if( S_OK == hr )
    {
        *ppTradePrice = pTradePrice;
        pTradePrice = NULL;

        _cwprintf(L"    Response has been prepared.\r\n");
    }

    _cwprintf(L"    Service method exit code: ");
    print_result( hr );

    // cleanup
    if( NULL != pTradePrice )
    {
        WSDFreeLinkedMemory( pTradePrice );
        pTradePrice = NULL;
    }

    return hr;
}