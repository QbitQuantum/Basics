void REXXENTRY invokeProgram(InstanceInfo *instanceInfo)
{
    RexxInstance *instance;
    RexxThreadContext *context;

    instanceInfo->code = 0;
    instanceInfo->rc = 0;
    strcpy(instanceInfo->returnResult, "");

    createInstance(instanceInfo, instance, context);

    RexxArrayObject args = context->NewArray(instanceInfo->argCount);
    for (size_t i = 0; i < instanceInfo->argCount; i++)
    {
        if (instanceInfo->arguments[i] != NULL)
        {
            context->ArrayPut(args, context->String(instanceInfo->arguments[i]), i + 1);
        }
    }

    RexxObjectPtr result = context->CallProgram(instanceInfo->programName, args);
    // if an exception occurred, get the decoded exception information
    if (context->CheckCondition())
    {
        RexxCondition condition;

        RexxDirectoryObject cond = context->GetConditionInfo();
        context->DecodeConditionInfo(cond, &condition);
        instanceInfo->code = condition.code;
        instanceInfo->rc = condition.rc;
    }
    else
    {
        if (result != NULLOBJECT)
        {
            CSTRING resultString = context->CString(result);
            strncpy(instanceInfo->returnResult, resultString, sizeof(instanceInfo->returnResult));
        }
    }
    // make sure we terminate this first
    instance->Terminate();
    deregisterExits();
    deregisterSubcomHandler();
}