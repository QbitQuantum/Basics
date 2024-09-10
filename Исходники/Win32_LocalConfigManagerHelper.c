MI_Result RepudicationHelper(
    _In_opt_ MI_Context* context,
    _In_ HANDLE token,
    _In_z_ const MI_Char* methodName,
    _Outptr_result_maybenull_ MI_Instance **cimErrorDetails)
{
    MI_Type type;
    MI_Value value;
    MI_Result result;
    size_t computerLength;
    DWORD sidLength;
    MI_Char* pComputerName=NULL;
    BOOL success = FALSE;
    PWSTR pstrUserSid = NULL;
    PTOKEN_USER userInformation = NULL;
    LCMProviderContext lcmContext = {0};

    if (context)
    {
        result = MI_Context_GetCustomOption(context,DSCCOMPUTERNAME, &type, &value);
        if (result == MI_RESULT_OK && type == MI_STRING)
        {
            computerLength = Tcslen(value.string)+1;
            pComputerName = (MI_Char*)DSC_malloc(computerLength* sizeof(wchar_t), NitsHere());
            if (pComputerName == NULL)
            {
                return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
            }

            memcpy(pComputerName, value.string, computerLength * sizeof(wchar_t));
        }
    }

    GetTokenInformation(token, TokenUser, userInformation, 0, &sidLength);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        if (pComputerName != NULL)
        {
            DSC_free(pComputerName);
        }

        return GetCimMIError(MI_RESULT_FAILED, cimErrorDetails, ID_LCMHELPER_COMPUTERNAMECONTEXT_ERROR);
    }

    userInformation = (PTOKEN_USER)DSC_malloc(sidLength, NitsHere());
    if (userInformation == NULL)
    {
        if (pComputerName != NULL)
        {
            DSC_free(pComputerName);
        }

        return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, cimErrorDetails, ID_LCMHELPER_MEMORY_ERROR);
    }

    success = GetTokenInformation(token, TokenUser, userInformation, sidLength, &sidLength);
    if (!success || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        if (pComputerName != NULL)
        {
            DSC_free(pComputerName);
        }

        DSC_free(userInformation);

        if (success)
        {
            // Pass through a bogus error if we've faulted in an error otherwise success will be returned.
            SetLastError(ERROR_ACCESS_DENIED);
        }
        return GetCimWin32Error(MI_RESULT_FAILED, cimErrorDetails, GetLastError());
    }

    success = ConvertSidToStringSidW(userInformation->User.Sid, &pstrUserSid);
    DSC_free(userInformation);
    if (!success || NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        if (pComputerName != NULL)
        {
            DSC_free(pComputerName);
        }
        if (pstrUserSid != NULL)
        {
            LocalFree(pstrUserSid);
        }

        if (success)
        {
            // Pass through a bogus error if we've faulted in an error otherwise success will be returned.
            SetLastError(ERROR_ACCESS_DENIED);
        }
        return GetCimWin32Error(MI_RESULT_FAILED, cimErrorDetails, GetLastError());
    }

    lcmContext.executionMode = (LCM_EXECUTIONMODE_OFFLINE | LCM_EXECUTIONMODE_ONLINE);
    lcmContext.context = (void*)context;
    LCM_WriteMessageInfo(&lcmContext, pComputerName, MI_WRITEMESSAGE_CHANNEL_VERBOSE, pstrUserSid);
    LocalFree(pstrUserSid);
    if (pComputerName != NULL)
    {
        DSC_free(pComputerName);
    }

    return MI_RESULT_OK;
}