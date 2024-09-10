void MI_CALL TEST_Stop_Invoke_SetTargetResource(
    _In_opt_ TEST_Stop_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Stop* instanceName,
    _In_opt_ const TEST_Stop_SetTargetResource* in)
{
    TEST_Stop_SetTargetResource out; 

    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    TEST_Stop_SetTargetResource_Construct(&out, context);    
    MI_Context_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Executing Set for Class TEST_Stop"));    
    TEST_Stop_SetTargetResource_Set_MIReturn(&out, 0 );
    MI_Context_PostInstance(context, &(out.__instance));
    TEST_Stop_SetTargetResource_Destruct(&out);    

    MI_Context_PostResult(context, MI_RESULT_OK);
}