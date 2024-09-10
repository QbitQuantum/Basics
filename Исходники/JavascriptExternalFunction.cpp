    void JavascriptExternalFunction::PrepareExternalCall(Js::Arguments * args)
    {
        ScriptContext * scriptContext = this->type->GetScriptContext();
        Assert(!scriptContext->GetThreadContext()->IsDisableImplicitException());
        scriptContext->VerifyAlive();

        Assert(scriptContext->GetThreadContext()->IsScriptActive());

        if (args->Info.Count == 0)
        {
            JavascriptError::ThrowTypeError(scriptContext, JSERR_This_NullOrUndefined);
        }

        Var &thisVar = args->Values[0];

        Js::TypeId typeId = Js::JavascriptOperators::GetTypeId(thisVar);

        this->callCount++;
        if (IS_JS_ETW(EventEnabledJSCRIPT_HOSTING_EXTERNAL_FUNCTION_CALL_START()))
        {
            JavascriptFunction* caller = nullptr;

            // Lot the caller function if the call count of the external function pass certain threshold (randomly pick 256)
            // we don't want to call stackwalk too often. The threshold can be adjusted as needed.
            if (callCount >= ETW_MIN_COUNT_FOR_CALLER && ((callCount % ETW_MIN_COUNT_FOR_CALLER) == 0))
            {
                Js::JavascriptStackWalker stackWalker(scriptContext);
                bool foundScriptCaller = false;
                while(stackWalker.GetCaller(&caller))
                {
                    if(caller != nullptr && Js::ScriptFunction::Is(caller))
                    {
                        foundScriptCaller = true;
                        break;
                    }
                }
                if(foundScriptCaller)
                {
                    Var sourceString = caller->EnsureSourceString();
                    Assert(JavascriptString::Is(sourceString));
                    const char16* callerString = Js::JavascriptString::FromVar(sourceString)->GetSz();
                    char16* outString = (char16*)callerString;
                    int length = 0;
                    if (wcschr(callerString, _u('\n')) != NULL || wcschr(callerString, _u('\n')) != NULL)
                    {
                        length = Js::JavascriptString::FromVar(sourceString)->GetLength();
                        outString = HeapNewArray(char16, length+1);
                        int j = 0;
                        for (int i = 0; i < length; i++)
                        {
                            if (callerString[i] != _u('\n') && callerString[i] != L'\r')
                            {
                                outString[j++] = callerString[i];
                            }
                        }
                        outString[j] = L'\0';
                    }
                    JS_ETW(EventWriteJSCRIPT_HOSTING_CALLER_TO_EXTERNAL(scriptContext, this, typeId, outString, callCount));
                    if (outString != callerString)
                    {
                        HeapDeleteArray(length+1, outString);
                    }
#if DBG_DUMP
                    if (Js::Configuration::Global.flags.Trace.IsEnabled(Js::HostPhase))
                    {
                        Output::Print(_u("Large number of Call to trampoline: methodAddr= %p, Object typeid= %d, caller method= %s, callcount= %d\n"),
                            this, typeId, callerString, callCount);
                    }
#endif
                }
            }
            JS_ETW(EventWriteJSCRIPT_HOSTING_EXTERNAL_FUNCTION_CALL_START(scriptContext, this, typeId));
#if DBG_DUMP
            if (Js::Configuration::Global.flags.Trace.IsEnabled(Js::HostPhase))
            {
                Output::Print(_u("Call to trampoline: methodAddr= %p, Object typeid= %d\n"), this, typeId);
            }
#endif
        }

        Js::RecyclableObject* directHostObject = nullptr;
        switch(typeId)
        {
        case TypeIds_Integer:
#if FLOATVAR
        case TypeIds_Number:
#endif // FLOATVAR
            Assert(!Js::RecyclableObject::Is(thisVar));
            break;
        default:
            {
                Assert(Js::RecyclableObject::Is(thisVar));

                ScriptContext* scriptContextThisVar = Js::RecyclableObject::FromVar(thisVar)->GetScriptContext();
                // We need to verify "this" pointer is active as well. The problem is that DOM prototype functions are
                // the same across multiple frames, and caller can do function.call(closedthis)
                Assert(!scriptContext->GetThreadContext()->IsDisableImplicitException());
                scriptContextThisVar->VerifyAlive();

                // translate direct host for fastDOM.
                switch(typeId)
                {
                case Js::TypeIds_GlobalObject:
                    {
                        Js::GlobalObject* srcGlobalObject = static_cast<Js::GlobalObject*>(thisVar);
                        directHostObject = srcGlobalObject->GetDirectHostObject();
                        // For jsrt, direct host object can be null. If thats the case don't change it.
                        if (directHostObject != nullptr)
                        {
                            thisVar = directHostObject;
                        }

                    }
                    break;
                case Js::TypeIds_Undefined:
                case Js::TypeIds_Null:
                    {
                        // Call to DOM function with this as "undefined" or "null"
                        // This should be converted to Global object
                        Js::GlobalObject* srcGlobalObject = scriptContextThisVar->GetGlobalObject() ;
                        directHostObject = srcGlobalObject->GetDirectHostObject();
                        // For jsrt, direct host object can be null. If thats the case don't change it.
                        if (directHostObject != nullptr)
                        {
                            thisVar = directHostObject;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }