PAL_Uint32 THREAD_API fireindication(void* param)
{
    Config* config = (Config*)param;
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 failAfterCount = config->failAfterCount;
    MI_Result failResult = config->failResult;

    Atomic_Swap( &config->threadrunning, 1);
    LOGMSG(("Set threadrunning to 1 for config (%p)", config));

    config->count = 0;
    LOGMSG(("Start to fireindication for class (%s)", config->className));

    /* wait for the semaphore */
    LOGMSG(("Wait for semaphore to fire indication"));
    Sem_Wait(&config->sem);
    LOGMSG(("Received semaphore and start firing indication"));

    if (config->testGroup == (MI_Uint32)TestGroup_Misc)
    {
        switch (config->miscTestSubGroup)
        {
        case MiscTestGroup_GetExpression:
        case MiscTestGroup_Evaluate:
        case MiscTestGroup_SelfTest:
            failAfterCount = 1;
            failResult = MI_RESULT_FAILED;
            break;
        default:
            break;
        }
    }

    while((MI_FALSE == config->disabled) && (config->count < failAfterCount))
    {
        config->count++;

        if (config->intervalMS > 0)
        {
            Sleep_Milliseconds(config->intervalMS);
        }
        if (r!= MI_RESULT_OK)
        {
            LOGMSG(("Set property value of indication failed (%d); Ignore #%d indication", r, config->count));
            continue;
        }
        if (config->lifecycleThreadControl == 0)
        {
            const MI_Char* bookmark = NULL;

            DEBUG_ASSERT( NULL != config->setprop );
            r = config->setprop(config->context, &config->indication);
            if (r == MI_RESULT_OK)
            {
                DEBUG_ASSERT( NULL != config->indication );

                if (config->subscribeBookmark &&
                    0 < Strlen(config->subscribeBookmark) &&
                    0 != Strcmp(config->subscribeBookmark, "."))
                {
                    // Only set bookmark if it is non-NULL and non-default
                    bookmark = ansiToMI(config->subscribeBookmark);
                }
                r = MI_Context_PostIndication(config->postctx, config->indication, 0, bookmark);
                if (r!= MI_RESULT_OK)
                {
                    LOGMSG(("Post #%d Indication failed (%d)", config->count, r));
                }

                /* Delete indication instance */
                MI_Instance_Delete( config->indication );
                config->indication = NULL;
            }
            else
            {
                LOGMSG(("config(%p:%s)->setprop failed to create indication instance(%d)", config, config->className, r));
            }
        }
        else
        {
            if (config->lifecycleContext && config->currentSubscriptionTypes != 0 && config->supportedSubscriptionTypes != 0)
            {
                // lifeCycleThreadControl other than 0 and a running thread indicates that we should schedule lifecycle events
                if (config->lifecycleThreadControl & MI_LIFECYCLE_INDICATION_CREATE)
                {
                    r = lifecycle_CreateInstance(config, config->lifecycleInstance);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("Lifecycle_CreateInstance for class (%s) failed with result (%d)", config->className, r));
                    }
                }
                if (config->lifecycleThreadControl & MI_LIFECYCLE_INDICATION_MODIFY)
                {
                    r = lifecycle_ModifyInstance(config->lifecycleInstance, config);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("Lifecycle_ModifyInstance for class (%s) failed with result (%d)", config->className, r));
                    }
                }
                if (config->lifecycleThreadControl & MI_LIFECYCLE_INDICATION_DELETE)
                {
                    r = lifecycle_DeleteInstance(config);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("Lifecycle_DeleteInstance for class (%s) failed with result (%d)", config->className, r));
                    }
                }
                if (config->lifecycleThreadControl & MI_LIFECYCLE_INDICATION_READ)
                {
                    r = lifecycle_EnumerateInstances(config);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("Lifecycle_EnumerateInstances for class (%s) failed with result (%d)", config->className, r));
                    }
                }
                if (config->lifecycleThreadControl & MI_LIFECYCLE_INDICATION_METHODCALL)
                {
                    r = lifecycle_InvokeMethod(config);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("Lifecycle_InvokeMethod for class (%s) failed with result (%d)", config->className, r));
                    }
                }
            }
        }
        LOGMSG(("Fired #%d indication for class (%s)", config->count, config->className));
    }

    Atomic_Swap( &config->threadrunning, 0);
    LOGMSG(("Set threadrunning to 0 for config (%p)", config));

    if (MI_FALSE == config->disabled)
    {
        LOGMSG(("fireindication stopped due to class (%s) need to fail after firing (%d) indicaitons", config->className, failAfterCount));
#if !defined(_MSC_VER)
        // if not joined yet, release thread resources
        pthread_detach(config->thread.__impl);
# endif
        if (failResult != MI_RESULT_OK)
        {
            if (config->lifecycleThreadControl == 0)
            {
                MI_Context_PostResult(config->postctx, failResult);
            }
            else
            {
                MI_LifecycleIndicationContext_PostResult(config->lifecycleContext, failResult);
            }
            LOGMSG(("Stop the fireindication and failed the operation with error (%s:%d)", config->className, failResult));
        }
    }
    else
        LOGMSG(("fireindication stopped due to disable indication called"));
    LOGMSG(("Done fireindication for class (%s)", config->className));
    return 0;
}