HRESULT CSoftHIDInputKbdMapper::FinalConstruct()
/*++
Routine Description:
    Overwrites the default FinalConstruct. Creates the default
    properties, gets pointer to COM task memory allocator.

Synchronization: 
    None
 
Arguments:
    None
    
Return Value:
    E_OUTOFMEMORY
        Could not create safearray for Report Descriptor data
    From called function
--*/
{
    BYTE HUGEP* pArrayData = NULL;
    HRESULT     hr = S_OK;

    IfFailHrGo(CoGetMalloc(1, &m_pMalloc));

    // Register notification messages
    IfFailHrGo(RegisterMessage(MSG_KEYTOUCHED, &m_KeyTouchedMsg));
    IfFailHrGo(RegisterMessage(MSG_OUTREPORTREADY, &m_OutReportReadyMsg));

    // Create safearray with Report Descriptor data
    m_psaReportDescriptor = SafeArrayCreateVector(VT_UI1, 0, sizeof(m_ReportDescriptor));
    IfFalseHrGo(NULL != m_psaReportDescriptor, E_OUTOFMEMORY);

    IfFailHrGo(::SafeArrayAccessData(m_psaReportDescriptor, (void HUGEP**)&pArrayData));

    // Copy Report Descriptor data into safearray
    CopyMemory(pArrayData, &m_ReportDescriptor, sizeof(m_ReportDescriptor));

    IfFailHrGo(::SafeArrayUnaccessData(m_psaReportDescriptor));

    // Start internal thread
    IfFailHrGo(CMessageTask::Start(DEFAULT_SYNC_DELAY));

    // Call OnConstruct method of CSoftHIDDevice class
    IfFailHrGo(CSoftHID::OnConstruct(this, m_OutReportReadyMsg));

Exit:
    return hr;

} // CSoftHIDInputKbdMapper::FinalConstruct