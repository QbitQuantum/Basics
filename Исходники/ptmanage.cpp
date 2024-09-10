/*++

Routine Name:

    CPTManager::GetMergedTicket

Routine Description:

    This routine retrieves a merged PrintTicket at the requested scope given the base
    and delta PrintTickets as IXMLDOMDocument2 interface pointers

Arguments:

    ptScope  - The scope at which the merge should take place
    pDelta   - The delta PrintTicket as an IXMLDOMDocument2 pointer
    pBase    - The base PrintTicket as an IXMLDOMDocument2 pointer
    ppResult - The resulting PrintTicket after the merge has completed

Return Value:

    HRESULT
    S_OK - On success
    E_*  - On error

--*/
HRESULT
CPTManager::GetMergedTicket(
    _In_        CONST EPrintTicketScope ptScope,
    _In_        CONST IXMLDOMDocument2* pDelta,
    _In_        IXMLDOMDocument2*       pBase,
    _Outptr_ IXMLDOMDocument2**      ppResult
    )
{
    ASSERTMSG(pDelta != NULL, "NULL PT reference part passed.\n");
    ASSERTMSG(pBase != NULL, "NULL base PT passed.\n");
    ASSERTMSG(ppResult != NULL, "NULL out PT passed.\n");

    HRESULT hr = S_OK;

    if (SUCCEEDED(hr = CHECK_HANDLE(m_hProvider, E_PENDING)) &&
        SUCCEEDED(hr = CHECK_POINTER(ppResult, E_POINTER)) &&
        SUCCEEDED(hr = CHECK_POINTER(pDelta, E_POINTER)) &&
        SUCCEEDED(hr = CHECK_POINTER(pBase, E_POINTER)))
    {
        *ppResult = NULL;
    }

    CComPtr<IStream> pResultStream(NULL);
    CComPtr<IStream> pBaseStream(NULL);
    CComPtr<IStream> pDeltaStream(NULL);

    CComPtr<IXMLDOMDocument2> pNewPT(NULL);

    //
    // Create a new DOM doc based off the result ticket and
    // assign to the resultant DOM doc
    //
    try
    {
        CComBSTR bstrErrorMessage;

        if (SUCCEEDED(hr) &&
            SUCCEEDED(hr = CreateStreamOnHGlobal(NULL, TRUE, &pResultStream)) &&
            SUCCEEDED(hr = pBase->QueryInterface(IID_IStream, reinterpret_cast<VOID**>(&pBaseStream)))  &&
            SUCCEEDED(hr = const_cast<IXMLDOMDocument2*>(pDelta)->QueryInterface(IID_IStream, reinterpret_cast<VOID**>(&pDeltaStream))))
        {
            if (SetThreadToken(NULL, m_hToken))
            {
                if (SUCCEEDED(hr = PTMergeAndValidatePrintTicket(m_hProvider,
                                                                 pBaseStream,
                                                                 pDeltaStream,
                                                                 ptScope,
                                                                 pResultStream,
                                                                 &bstrErrorMessage)))
                {
                    if (SUCCEEDED(hr = SetPTFromStream(pResultStream, &pNewPT)))
                    {
                        //
                        // Assign the outgoing element pointer - detach from CComPtr to release ownership
                        //
                        *ppResult = pNewPT.Detach();
                    }
                }
                else
                {
                    CStringXDA cstrMessage;
                    CStringXDA cstrError(bstrErrorMessage);
                    cstrMessage.Format("PTMergeAndValidatePrintTicket failed with message: %s\n", cstrError);

                    ERR(cstrMessage.GetBuffer());
                }

                //
                // Always revert back to the default security context
                //
                if (!SetThreadToken(NULL, NULL))
                {
                    //
                    // We couldn't revert the security context. The filter pipeline
                    // manager will clean up the thread when operation is complete,
                    // when it is determined that the security context was not 
                    // reverted. Since there are no security implications with 
                    // running this filter in an elevated context, we can 
                    // continue to run.
                    //
                }
            }
            else
            {
                hr = HRESULT_FROM_WIN32(GetLastError());

                //
                // If SetThreadToken fails, GetLastError will return an error
                //
                _Analysis_assume_(FAILED(hr));
            }
        }
    }
    catch (CXDException& e)
    {
        hr = e;
    }

    ERR_ON_HR(hr);
    return hr;
}