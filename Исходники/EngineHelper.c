MI_Result GetCimWin32Error(MI_Uint32 result ,
                           _Outptr_result_maybenull_ MI_Instance **cimErrorDetails,
                           _In_ MI_Uint32 errorStringId )
{
    Intlstr intlstr = Intlstr_Null;
    GetResourceString(errorStringId, &intlstr);

    MI_Utilities_CimErrorFromErrorCode( (MI_Uint32)result, MI_RESULT_TYPE_WIN32, intlstr.str, cimErrorDetails);
    strncpy(g_currentError, intlstr.str, 5000);
    DSC_EventWriteCIMError(intlstr.str,(MI_Uint32)result);
    if( intlstr.str)
        Intlstr_Free(intlstr);
#if defined(_MSC_VER)
    return MIResultFromHRESULT(HRESULT_FROM_WIN32(result));
#else
    return MI_RESULT_FAILED;
#endif
}