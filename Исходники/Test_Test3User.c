void MI_CALL TEST_Test3User_Invoke_SetTargetResource(
    _In_opt_ TEST_Test3User_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TEST_Test3User* instanceName,
    _In_opt_ const TEST_Test3User_SetTargetResource* in)
{
    TEST_Test3User_SetTargetResource out;  
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    TEST_Test3User_SetTargetResource_Construct(&out, context);
    TEST_Test3User_SetTargetResource_Set_MIReturn(&out, 0 );
    MI_Context_PostInstance(context, &(out.__instance));
    TEST_Test3User_SetTargetResource_Destruct(&out);    

    MI_Context_PostResult(context, MI_RESULT_OK);

}