CHAKRA_API JsDiagSetStepType(
    _In_ JsDiagStepType stepType)
{
#ifndef ENABLE_SCRIPT_DEBUGGING
    return JsErrorCategoryUsage;
#else
    return ContextAPIWrapper_NoRecord<true>([&](Js::ScriptContext * scriptContext) -> JsErrorCode {

        JsrtContext *currentContext = JsrtContext::GetCurrent();
        JsrtRuntime* runtime = currentContext->GetRuntime();

        VALIDATE_RUNTIME_IS_AT_BREAK(runtime);

        JsrtDebugManager* jsrtDebugManager = runtime->GetJsrtDebugManager();

        VALIDATE_IS_DEBUGGING(jsrtDebugManager);

        if (stepType == JsDiagStepTypeStepIn)
        {
            jsrtDebugManager->SetResumeType(BREAKRESUMEACTION_STEP_INTO);
        }
        else if (stepType == JsDiagStepTypeStepOut)
        {
           jsrtDebugManager->SetResumeType(BREAKRESUMEACTION_STEP_OUT);
        }
        else if (stepType == JsDiagStepTypeStepOver)
        {
            jsrtDebugManager->SetResumeType(BREAKRESUMEACTION_STEP_OVER);
        }
        else if (stepType == JsDiagStepTypeStepBack)
        {
#if ENABLE_TTD
            ThreadContext* threadContext = runtime->GetThreadContext();
            if(!threadContext->IsRuntimeInTTDMode())
            {
                //Don't want to fail hard when user accidentally clicks this so pring message and step forward
                fprintf(stderr, "Must be in replay mode to use reverse-step - launch with \"--replay-debug\" flag in Node.");
                jsrtDebugManager->SetResumeType(BREAKRESUMEACTION_STEP_OVER);
            }
            else
            {
                threadContext->TTDExecutionInfo->SetPendingTTDStepBackMove();

                //don't worry about BP suppression because we are just going to throw after we return
                jsrtDebugManager->SetResumeType(BREAKRESUMEACTION_CONTINUE);
            }
#else
            return JsErrorInvalidArgument;
#endif
        }
        else if (stepType == JsDiagStepTypeReverseContinue)
        {
#if ENABLE_TTD
            ThreadContext* threadContext = runtime->GetThreadContext();
            if(!threadContext->IsRuntimeInTTDMode())
            {
                //Don't want to fail hard when user accidentally clicks this so pring message and step forward
                fprintf(stderr, "Must be in replay mode to use reverse-continue - launch with \"--replay-debug\" flag in Node.");
                jsrtDebugManager->SetResumeType(BREAKRESUMEACTION_CONTINUE);
            }
            else
            {
                threadContext->TTDExecutionInfo->SetPendingTTDReverseContinueMove(JsTTDMoveMode::JsTTDMoveScanIntervalForContinue);

                //don't worry about BP suppression because we are just going to throw after we return
                jsrtDebugManager->SetResumeType(BREAKRESUMEACTION_CONTINUE);
            }
#else
            return JsErrorInvalidArgument;
#endif
        }
        else if (stepType == JsDiagStepTypeContinue)
        {
            jsrtDebugManager->SetResumeType(BREAKRESUMEACTION_CONTINUE);
        }

        return JsNoError;
    });
#endif
}