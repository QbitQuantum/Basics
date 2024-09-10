void MI_CALL MSFT_DSCLocalConfigManager_Invoke_GetConfiguration(
    _In_opt_ MSFT_DSCLocalConfigManager_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_DSCLocalConfigManager* instanceName,
    _In_opt_ const MSFT_DSCLocalConfigManager_GetConfiguration* in)
{
    MI_Result miResult;
    MI_Instance *cimErrorDetails = NULL;
    MI_InstanceA outInstances = {0};
    MI_Value val;
    MI_Uint32 bufferIndex = 0;    
    MSFT_DSCLocalConfigManager_GetConfiguration outputObject;
    HANDLE m_clientThreadToken;
    
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

            
    if(!in->configurationData.exists)
    {
        MI_Context_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;        
    }

    if(!OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE | TOKEN_QUERY | TOKEN_DUPLICATE, TRUE, &m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_THREADIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    if (!SetThreadToken(NULL, NULL))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_REVERTSELF_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        return;
    }

    miResult = MSFT_DSCLocalConfigManager_GetConfiguration_Construct(&outputObject, context);
    if(miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_CONSTRUCTGET_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }   

    GetRealBufferIndex( &(in->configurationData.value), &bufferIndex);
    miResult = CallGetConfiguration(in->configurationData.value.data + bufferIndex, 
                                in->configurationData.value.size - bufferIndex, &outInstances, 
                                context, &cimErrorDetails);
    if(miResult != MI_RESULT_OK)
    {
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        MSFT_DSCLocalConfigManager_GetConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        return;
    }
   
    val.instancea.data = outInstances.data;
    val.instancea.size = outInstances.size;
    miResult = MI_Context_WriteStreamParameter(context, L"configurations", &val, MI_INSTANCEA, 0);
    CleanUpInstanceCache(&outInstances);
    if(miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_WRITEGET_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        MSFT_DSCLocalConfigManager_GetConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        return;
    }

    miResult = MSFT_DSCLocalConfigManager_GetConfiguration_Set_MIReturn(&outputObject, 0);
    if(miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_SETGET_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        MSFT_DSCLocalConfigManager_GetConfiguration_Destruct(&outputObject);
        SetThreadToken(NULL, m_clientThreadToken);
        CloseHandle(m_clientThreadToken);
        return;
    }

    miResult = MSFT_DSCLocalConfigManager_GetConfiguration_Post(&outputObject, context);
    MSFT_DSCLocalConfigManager_GetConfiguration_Destruct(&outputObject);

    if (!SetThreadToken(NULL, m_clientThreadToken))
    {
        GetCimWin32Error(GetLastError(), &cimErrorDetails, ID_LCMHELPER_RESUMEIMPERSONATION_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        CloseHandle(m_clientThreadToken);
        return;
    }

    CloseHandle(m_clientThreadToken);

    if(miResult != MI_RESULT_OK)
    {
        GetCimMIError(miResult, &cimErrorDetails, ID_LCMHELPER_POSTGET_FAILED);
        MI_PostCimError(context, cimErrorDetails);
        MI_Instance_Delete(cimErrorDetails);
        return;
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}