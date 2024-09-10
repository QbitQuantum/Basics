static MI_Result MI_CALL CreateOMIError_shared(
    _In_z_ const MI_Char* message,
    MI_Uint32 errorCode, 
    _In_z_ const MI_Char* errorType, 
    MI_Uint16 errorCategory, 
    const MI_ClassDecl *classDecl,
    _Outptr_ MI_Instance **omiError)
{
    MI_Result   result = MI_RESULT_OK;
    OMI_Error *err = NULL;
    MI_Application application = {0};
    *omiError = NULL;

    result = MI_Application_Initialize(0, NULL, omiError, &application);
    if (result != MI_RESULT_OK)
        return result;

    result = MI_Application_NewInstance(&application, classDecl->name, classDecl, (MI_Instance**)&err); 
    if (result == MI_RESULT_OK)
    {
        result = OMI_Error_Set_Message(err, message);
        if (result != MI_RESULT_OK) goto Exit;
        result = OMI_Error_Set_error_Code(err, errorCode);
        if (result != MI_RESULT_OK) goto Exit;
        result = OMI_Error_Set_error_Type(err, errorType); 
        if (result != MI_RESULT_OK) goto Exit;
        result = OMI_Error_Set_error_Category(err, errorCategory);
        if (result != MI_RESULT_OK) goto Exit;
                result = OMI_Error_Set_CIMStatusCode(err, MI_RESULT_FAILED);
        if (result != MI_RESULT_OK) goto Exit;
        *omiError = (MI_Instance*)err;
    }

Exit:
    if ((result != MI_RESULT_OK) && err) MI_Instance_Delete((MI_Instance*)err); 
    MI_Application_Close(&application);
    return result;
}