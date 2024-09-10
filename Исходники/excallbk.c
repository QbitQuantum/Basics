BOOLEAN
ndisprotRegisterExCallBack()
{
    OBJECT_ATTRIBUTES   ObjectAttr;
    UNICODE_STRING      CallBackObjectName;
    NTSTATUS            Status;
    BOOLEAN             bResult = TRUE;

    DEBUGP(DL_LOUD, ("--> ndisprotRegisterExCallBack\n"));

    PAGED_CODE();

    do {

        RtlInitUnicodeString(&CallBackObjectName, NDISPROT_CALLBACK_NAME);

        InitializeObjectAttributes(&ObjectAttr,
                                   &CallBackObjectName,
                                   OBJ_CASE_INSENSITIVE | OBJ_PERMANENT,
                                   NULL,
                                   NULL);

        Status = ExCreateCallback(&CallbackObject,
                                  &ObjectAttr,
                                  TRUE,
                                  TRUE);


        if (!NT_SUCCESS(Status)) {

            DEBUGP(DL_ERROR, ("RegisterExCallBack: failed to create callback %lx\n", Status));
            bResult = FALSE;
            break;
        }

        CallbackRegisterationHandle = ExRegisterCallback(CallbackObject,
                                                                 ndisprotCallback,
                                                                 (PVOID)NULL);
        if (CallbackRegisterationHandle == NULL) {
            DEBUGP(DL_ERROR,("RegisterExCallBack: failed to register a Callback routine%lx\n", Status));
            bResult = FALSE;
            break;
        }

        ExNotifyCallback(CallbackObject,
                        (PVOID)CALLBACK_SOURCE_NDISPROT,
                        (PVOID)NULL);


    }WHILE(FALSE);

    if(!bResult) {
        if (CallbackRegisterationHandle) {
            ExUnregisterCallback(CallbackRegisterationHandle);
            CallbackRegisterationHandle = NULL;
        }

        if (CallbackObject) {
            ObDereferenceObject(CallbackObject);
            CallbackObject = NULL;
        }
    }

    DEBUGP(DL_LOUD, ("<-- ndisprotRegisterExCallBack\n"));

    return bResult;

}