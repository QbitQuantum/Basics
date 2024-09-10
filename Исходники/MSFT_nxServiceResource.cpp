void MI_CALL MSFT_nxServiceResource_Invoke_GetTargetResource(
    _In_opt_ MSFT_nxServiceResource_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_nxServiceResource* instanceName,
    _In_opt_ const MSFT_nxServiceResource_GetTargetResource* in)
{
    std::cerr << "Get" << std::endl;

    MI_Result r = MI_RESULT_OK;
    MI_Boolean res = MI_TRUE;
    MSFT_nxServiceResource_GetTargetResource out;
    MI_Instance *newInstance;
    MI_Value value;

    r = MSFT_nxServiceResource_GetTargetResource_Construct(&out, context);
    r = MSFT_nxServiceResource_GetTargetResource_Set_MIReturn(&out, 0);

    const MSFT_nxServiceResource * service = in->InputResource.value;
    r = MI_Instance_Clone(&service->__instance, &newInstance);


    std::vector<std::string> ret_strings;
    long exit_code = callPythonFunction(
        ret_strings,
        self->pGetFn,
        4,
        PassString(service->Name),
        PassString(service->Controller),
        PassBoolean(service->Enabled),
        PassString(service->State));
    
    // Expecting 4+1 parameters in return
    if (ret_strings.size() == (4+1) && exit_code == 0)
    {
        res = MI_TRUE;
    }
    else
    {
        MI_Context_PostResult(context, MI_RESULT_FAILED);
        return;
    }

    if (SetElement(newInstance, "Name", ret_strings[0], MI_STRING)  != 0 ||
        SetElement(newInstance, "Controller", ret_strings[1], MI_STRING)  != 0 ||
        SetElement(newInstance, "Enabled", ret_strings[2], MI_BOOLEAN)  != 0 ||
        SetElement(newInstance, "State", ret_strings[3], MI_STRING)  != 0 ||
        SetElement(newInstance, "Path", ret_strings[4], MI_STRING))
    {
        MI_Context_PostResult(context, MI_RESULT_FAILED);
        return;
    }

    value.instance = newInstance;
    r = MI_Instance_SetElement(&out.__instance, "OutputResource", &value, MI_INSTANCE, 0);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult(context, r);
        return;
    }

    MI_Instance_Delete(newInstance);
    r = MSFT_nxServiceResource_GetTargetResource_Post(&out, context);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult(context, r);
        return;
    }

    r = MSFT_nxServiceResource_GetTargetResource_Destruct(&out);
    if ( r != MI_RESULT_OK )
    {
        MI_Context_PostResult(context, r);
        return;
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}