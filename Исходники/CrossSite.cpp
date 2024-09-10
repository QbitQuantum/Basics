    Var CrossSite::CommonThunk(RecyclableObject* recyclableObject, JavascriptMethod entryPoint, Arguments args)
    {
        DynamicObject* function = DynamicObject::FromVar(recyclableObject);

        FunctionInfo * functionInfo = (JavascriptFunction::Is(function) ? JavascriptFunction::FromVar(function)->GetFunctionInfo() : nullptr);
        AutoDisableRedeferral autoDisableRedeferral(functionInfo);

        ScriptContext* targetScriptContext = function->GetScriptContext();
        Assert(!targetScriptContext->IsClosed());
        Assert(function->IsExternal() || function->IsCrossSiteObject());
        Assert(targetScriptContext->GetThreadContext()->IsScriptActive());

        HostScriptContext* calleeHostScriptContext = targetScriptContext->GetHostScriptContext();
        HostScriptContext* callerHostScriptContext = targetScriptContext->GetThreadContext()->GetPreviousHostScriptContext();

        if (callerHostScriptContext == calleeHostScriptContext || (callerHostScriptContext == nullptr && !calleeHostScriptContext->HasCaller()))
        {
            return JavascriptFunction::CallFunction<true>(function, entryPoint, args, true /*useLargeArgCount*/);
        }

#if DBG_DUMP || defined(PROFILE_EXEC) || defined(PROFILE_MEM)
        calleeHostScriptContext->EnsureParentInfo(callerHostScriptContext->GetScriptContext());
#endif

        TTD_XSITE_LOG(recyclableObject->GetScriptContext(), "CommonThunk -- Pass Through", recyclableObject);

        uint i = 0;
        if (args.Values[0] == nullptr)
        {
            i = 1;
            Assert(args.IsNewCall());
            Assert(JavascriptProxy::Is(function) || (JavascriptFunction::Is(function) && JavascriptFunction::FromVar(function)->GetFunctionInfo()->GetAttributes() & FunctionInfo::SkipDefaultNewObject));
        }
        uint count = args.Info.Count;
        for (; i < count; i++)
        {
            args.Values[i] = CrossSite::MarshalVar(targetScriptContext, args.Values[i]);
        }
        if (args.HasExtraArg())
        {
            // The final eval arg is a frame display that needs to be marshaled specially.
            args.Values[count] = CrossSite::MarshalFrameDisplay(targetScriptContext, args.GetFrameDisplay());
        }
        

#if ENABLE_NATIVE_CODEGEN
        CheckCodeGenFunction checkCodeGenFunction = GetCheckCodeGenFunction(entryPoint);
        if (checkCodeGenFunction != nullptr)
        {
            ScriptFunction* callFunc = ScriptFunction::FromVar(function);
            entryPoint = checkCodeGenFunction(callFunc);
            Assert(CrossSite::IsThunk(function->GetEntryPoint()));
        }
#endif

        // We need to setup the caller chain when we go across script site boundary. Property access
        // is OK, and we need to let host know who the caller is when a call is from another script site.
        // CrossSiteObject is the natural place but it is in the target site. We build up the site
        // chain through PushDispatchExCaller/PopDispatchExCaller, and we call SetCaller in the target site
        // to indicate who the caller is. We first need to get the site from the previously pushed site
        // and set that as the caller for current call, and push a new DispatchExCaller for future calls
        // off this site. GetDispatchExCaller and ReleaseDispatchExCaller is used to get the current caller.
        // currentDispatchExCaller is cached to avoid multiple allocations.
        IUnknown* sourceCaller = nullptr, *previousSourceCaller = nullptr;
        HRESULT hr = NOERROR;
        Var result = nullptr;
        BOOL wasDispatchExCallerPushed = FALSE, wasCallerSet = FALSE;

        TryFinally([&]()
        {
            hr = callerHostScriptContext->GetDispatchExCaller((void**)&sourceCaller);

            if (SUCCEEDED(hr))
            {
                hr = calleeHostScriptContext->SetCaller((IUnknown*)sourceCaller, (IUnknown**)&previousSourceCaller);
            }

            if (SUCCEEDED(hr))
            {
                wasCallerSet = TRUE;
                hr = calleeHostScriptContext->PushHostScriptContext();
            }
            if (FAILED(hr))
            {
                // CONSIDER: Should this be callerScriptContext if we failed?
                JavascriptError::MapAndThrowError(targetScriptContext, hr);
            }
            wasDispatchExCallerPushed = TRUE;

            result = JavascriptFunction::CallFunction<true>(function, entryPoint, args, true /*useLargeArgCount*/);
            ScriptContext* callerScriptContext = callerHostScriptContext->GetScriptContext();
            result = CrossSite::MarshalVar(callerScriptContext, result);
        },
        [&](bool hasException)
        {
            if (sourceCaller != nullptr)
            {
                callerHostScriptContext->ReleaseDispatchExCaller(sourceCaller);
            }
            IUnknown* originalCaller = nullptr;
            if (wasDispatchExCallerPushed)
            {
                calleeHostScriptContext->PopHostScriptContext();
            }
            if (wasCallerSet)
            {
                calleeHostScriptContext->SetCaller(previousSourceCaller, &originalCaller);
                if (previousSourceCaller)
                {
                    previousSourceCaller->Release();
                }
                if (originalCaller)
                {
                    originalCaller->Release();
                }
            }
        });
        Assert(result != nullptr);
        return result;
    }