MI_Result UpdateServerURLsToDSCCache(
    _In_ RegistrationManager *self,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    MI_Application miApp = MI_APPLICATION_NULL;
    MI_Result result = MI_RESULT_OK;
    MI_Char* serverURLs = NULL;
        
    result = DSC_MI_Application_Initialize(0, NULL, NULL, &miApp);
    if (result != MI_RESULT_OK)
    {
        EH_Fail_(GetCimMIError(result, cimErrorDetails, ID_MODMAN_APPINIT_FAILED));
    }    

    result = FormatServerURLsForDscCache(self, &serverURLs, cimErrorDetails);
    EH_CheckResult(result);

    result = UpdateCurrentStatus(NULL, NULL, NULL, serverURLs, cimErrorDetails);
    EH_CheckResult(result);

    EH_UNWIND:
    if (serverURLs)
    {
        DSC_free(serverURLs);
    }
    MI_Application_Close(&miApp);    
    return result;
}