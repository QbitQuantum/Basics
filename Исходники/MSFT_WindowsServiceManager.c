void MI_CALL MSFT_WindowsServiceManager_Invoke_GetWindowsServices(
    _In_opt_ MSFT_WindowsServiceManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_WindowsServiceManager* instanceName,
    _In_opt_ const MSFT_WindowsServiceManager_GetWindowsServices* in)
{
    MI_Result result;
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);

    result = Invoke_GetWindowsServices(context, in);

    MI_Context_PostResult(context, result);
}