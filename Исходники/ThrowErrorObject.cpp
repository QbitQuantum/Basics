    // In some cases we delay throw from helper methods and return ThrowErrorObject instead which we call and throw later.
    // Then the exception is actually thrown when we call this method.
    Var ThrowErrorObject::DefaultEntryPoint(RecyclableObject* function, CallInfo callInfo, ...)
    {
        ARGUMENTS(args, callInfo);
        ScriptContext* scriptContext = function->GetScriptContext();

        ThrowErrorObject* throwErrorObject = ThrowErrorObject::FromVar(function);

#ifdef ENABLE_SCRIPT_DEBUGGING
        bool useExceptionWrapper =
            scriptContext->IsScriptContextInDebugMode() /* Check for script context is intentional as library code also uses exception wrapper */ &&
            (ScriptContext::IsExceptionWrapperForBuiltInsEnabled(scriptContext) || ScriptContext::IsExceptionWrapperForHelpersEnabled(scriptContext)) &&
            !AutoRegisterIgnoreExceptionWrapper::IsRegistered(scriptContext->GetThreadContext());

        if (useExceptionWrapper)
        {
            // Forward the throw via regular try-catch wrapper logic that we use for helper/library calls.
            AutoRegisterIgnoreExceptionWrapper autoWrapper(scriptContext->GetThreadContext());

            Var ret = HelperOrLibraryMethodWrapper<true>(scriptContext, [throwErrorObject, scriptContext]() -> Var {
                JavascriptExceptionOperators::Throw(throwErrorObject->m_error, scriptContext);
            });
            return ret;
        }
        else
#endif
        {
            JavascriptExceptionOperators::Throw(throwErrorObject->m_error, scriptContext);
        }
    }