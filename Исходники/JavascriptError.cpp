    void JavascriptError::SetErrorMessage(JavascriptError *pError, HRESULT hr, ScriptContext* scriptContext, va_list argList)
    {
        Assert(FAILED(hr));
        char16 * allocatedString = nullptr;

        if (FACILITY_CONTROL == HRESULT_FACILITY(hr) || FACILITY_JSCRIPT == HRESULT_FACILITY(hr))
        {
            if (argList != nullptr)
            {
                HRESULT hrAdjusted = GetAdjustedResourceStringHr(hr, /* isFormatString */ true);

                BSTR message = BstrGetResourceString(hrAdjusted);
                if (message != nullptr)
                {
                    size_t len = _vscwprintf(message, argList);
                    Assert(len > 0);
                    len = AllocSizeMath::Add(len, 1);
                    allocatedString = RecyclerNewArrayLeaf(scriptContext->GetRecycler(), char16, len);

#pragma prefast(push)
#pragma prefast(disable:26014, "allocatedString allocated size more than msglen")
#pragma prefast(disable:26000, "allocatedString allocated size more than msglen")
                    len = vswprintf_s(allocatedString, len, message, argList);
                    Assert(len > 0);
#pragma prefast(pop)

                    SysFreeString(message);
                }
            }
            if (allocatedString == nullptr)
            {
                HRESULT hrAdjusted = GetAdjustedResourceStringHr(hr, /* isFormatString */ false);

                BSTR message = BstrGetResourceString(hrAdjusted);
                if (message == nullptr)
                {
                    message = BstrGetResourceString(IDS_UNKNOWN_RUNTIME_ERROR);
                }
                if (message != nullptr)
                {
                    uint32 len = SysStringLen(message) +1;
                    allocatedString = RecyclerNewArrayLeaf(scriptContext->GetRecycler(), char16, len);
                    wcscpy_s(allocatedString, len, message);
                    SysFreeString(message);
                }
            }
        }
        JavascriptError::SetErrorMessageProperties(pError, hr, allocatedString, scriptContext);
    }