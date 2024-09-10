const MI_Char *  LogCADebugMessage(_In_ void *provContext,_In_opt_z_ const MI_Char *message)
{
    MI_Result result = MI_RESULT_OK;
    if(message != NULL && provContext != NULL)
    {
        ProviderCallbackContext *providerContext = (ProviderCallbackContext *) provContext;
        LCMProviderContext *lcmContext = providerContext->lcmProviderContext;


        if((lcmContext->executionMode & LCM_EXECUTIONMODE_ONLINE) && lcmContext->context)
        {
             MI_Char *fullMessage = NULL;
            size_t msgLen;
            msgLen = Tcslen(message) + Tcslen(providerContext->resourceId) + Tcslen(VERBOSE_FORMAT)+Tcslen(EMPTY_STRING)+Tcslen(g_CAJobInformation.deviceName)+TOKENIZED_MESSAGE_PADDING; //'ResourceId': <message>\0
            fullMessage = (MI_Char*) DSC_malloc(sizeof(MI_Char)*msgLen, NitsHere());

            if(fullMessage != NULL)
            {
                if(Stprintf(fullMessage, msgLen,VERBOSE_FORMAT , g_CAJobInformation.deviceName, EMPTY_STRING, providerContext->resourceId, message) >0 )
                {
                    result = MI_Context_WriteDebug((MI_Context*) lcmContext->context, fullMessage);

                    if(result != MI_RESULT_OK)
                    {
                        // Ignore the failure, this doesn't impact the functionality.
                    }
                }
                //Return the message since the event is output from the parent rfunction
                return fullMessage;
            }
        }
    }
    return NULL;
}