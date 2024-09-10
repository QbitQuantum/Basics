FCIMPL2(void, COMCurrency::DoToDecimal, DECIMAL * result, CY c)
{
    CONTRACTL
    {
        THROWS;
        DISABLED(GC_TRIGGERS);
        MODE_COOPERATIVE;
        SO_TOLERANT;		
    } CONTRACTL_END;
    
    // GC could only happen when exception is thrown, no need to protect result
    HELPER_METHOD_FRAME_BEGIN_0();
    //-[autocvtpro]-------------------------------------------------------

    _ASSERTE(result);
    HRESULT hr = VarDecFromCy(c, result);
    if (FAILED(hr))
    {
        // Didn't expect to get here.  Update code for this HR.
        _ASSERTE(S_OK == hr);
        COMPlusThrowHR(hr);
    }

    if (FAILED(DecimalCanonicalize(result)))
        COMPlusThrow(kOverflowException, L"Overflow_Currency");
    
    result->wReserved = 0;

    //-[autocvtepi]-------------------------------------------------------
    HELPER_METHOD_FRAME_END();
}