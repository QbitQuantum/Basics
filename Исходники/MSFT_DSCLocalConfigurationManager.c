void MI_CALL MSFT_DSCLocalConfigurationManager_Invoke_PerformRequiredConfigurationChecks(
    _In_opt_ MSFT_DSCLocalConfigurationManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigurationManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks* in)
{
    SetJobId();
    
    // Debug Log 
    DSC_EventWriteMSFTMethodParameters(__WFUNCTION__,className,methodName,nameSpace);
    if (!in->Flags.exists || !(in->Flags.value == TASK_REGULAR || in->Flags.value == TASK_REBOOT || in->Flags.value == TASK_BOOTSTRAP ))
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        ResetJobId();
        return;        
    }
    Invoke_PerformRequiredConfigurationChecks(self, context, nameSpace, className, methodName, instanceName, in);

}