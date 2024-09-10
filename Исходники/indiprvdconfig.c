/* Get config from instance */
_Use_decl_annotations_
MI_Result Config_FromInstance(
    Batch* batch,
    const MI_Instance *instance,
    Config* config)
{
    MI_Value v;
    MI_Type t;
    MI_Uint32 f;
    MI_Result r;
    memset((void*)config, 0, sizeof(Config));
    r = MI_Instance_GetElement(instance, MI_T("className"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (v.string)
        config->className = (const char*)Batch_ZStrdup(batch, v.string);
    
    r = MI_Instance_GetElement(instance, MI_T("configFilepath"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (v.string)
        config->configFilepath = (const char*)Batch_ZStrdup(batch, v.string);
    
    r = MI_Instance_GetElement(instance, MI_T("testGroup"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->testGroup = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("testGroup"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->testGroup = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("intervalMS"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->intervalMS = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("failAfterCount"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->failAfterCount = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("failResult"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->failResult = (MI_Result)v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("initBehavior"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->initBehavior = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("initResultCode"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->initResultCode = (MI_Result)v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("initTimeoutMS"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->initTimeoutMS = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("finalizeBehavior"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->finalizeBehavior = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("finalizeResultCode"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->finalizeResultCode = (MI_Result)v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("postBehavior"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->postBehavior = v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("miscTestSubGroup"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->miscTestSubGroup = v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("subscribeBookmark"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (v.string)
        config->subscribeBookmark = Batch_ZStrdup(batch, v.string);

    r = MI_Instance_GetElement(instance, MI_T("providerBookmark"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (v.string)
        config->providerBookmark = Batch_ZStrdup(batch, v.string);

    r = MI_Instance_GetElement(instance, MI_T("dialect"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (v.string)
        config->dialect = Batch_ZStrdup(batch, v.string);

    r = MI_Instance_GetElement(instance, MI_T("expression"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (v.string)
        config->expression = Batch_ZStrdup(batch, v.string);

    r = MI_Instance_GetElement(instance, MI_T("evalResult"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->evalResult = v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("logLoadUnloadCall"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->logLoadUnloadCall = v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("currentSubscriptionTypes"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->currentSubscriptionTypes = v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("supportedSubscriptionTypes"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->supportedSubscriptionTypes = v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("apicallseq"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (t != MI_STRINGA)
        return MI_RESULT_INVALID_PARAMETER;

    {
        MI_Uint32 count = MAXLOGENTRY;
        MI_Uint32 i;
        if (v.stringa.size < count)
            count =v.stringa.size;
        if (v.stringa.data)
        {
            for (i = 0; i < count; i++)
            {
                if (v.stringa.data[i])
                {
                    char *str = Batch_ZStrdup(batch, v.stringa.data[i]);
                    if (!str)
                        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
                    config->apicallseq[i] = str;
                }
            }
        }
        config->apicallseqcount = count;
    }
    return r;
}