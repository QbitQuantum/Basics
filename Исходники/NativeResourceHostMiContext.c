static MI_Result WriteError(_In_ MI_Context* context, MI_Uint32 resultCode, _In_z_ const MI_Char* resultType, _In_z_ const MI_Char* errorMessage, _Out_ MI_Boolean *flag)
{
    MI_Result returnValue = MI_RESULT_OK;
    MI_Instance* extendedError = NULL;

    NativeResourceProvider* nativeResourceProvider = (NativeResourceProvider*)context;

    if (!nativeResourceProvider->_private.resourceProviderClassLoaded) {
        DSC_EventUnSupportedHostMethodCalled(MI_T("PostIndication"));
        return MI_RESULT_NOT_SUPPORTED;
    }

    *flag = MI_TRUE; // TRUE indicates the provider can continue (this is a non-terminating error)

    returnValue = MI_Utilities_CimErrorFromErrorCode(resultCode, resultType, errorMessage, &extendedError);
    EH_CheckResult(returnValue);

    DoWriteError(NULL, nativeResourceProvider->_private.callbackContext, extendedError, NULL);

EH_UNWIND;
    if (extendedError != NULL)
        MI_Instance_Delete(extendedError);

    return returnValue;
}