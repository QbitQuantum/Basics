    Var JavascriptGeneratorFunction::EntryAsyncFunctionImplementation(RecyclableObject* function, CallInfo callInfo, ...)
    {
        PROBE_STACK(function->GetScriptContext(), Js::Constants::MinStackDefault);
        ARGUMENTS(stackArgs, callInfo);

        ScriptContext* scriptContext = function->GetScriptContext();
        JavascriptLibrary* library = scriptContext->GetLibrary();
        RecyclableObject* prototype = scriptContext->GetLibrary()->GetNull();

        // InterpreterStackFrame takes a pointer to the args, so copy them to the recycler heap
        // and use that buffer for this InterpreterStackFrame.
        Field(Var)* argsHeapCopy = RecyclerNewArray(scriptContext->GetRecycler(), Field(Var), stackArgs.Info.Count);
        CopyArray(argsHeapCopy, stackArgs.Info.Count, stackArgs.Values, stackArgs.Info.Count);
        Arguments heapArgs(callInfo, (Var*)argsHeapCopy);

        JavascriptExceptionObject* e = nullptr;
        JavascriptPromiseResolveOrRejectFunction* resolve;
        JavascriptPromiseResolveOrRejectFunction* reject;
        JavascriptPromiseAsyncSpawnExecutorFunction* executor =
            library->CreatePromiseAsyncSpawnExecutorFunction(
                JavascriptPromise::EntryJavascriptPromiseAsyncSpawnExecutorFunction,
                scriptContext->GetLibrary()->CreateGenerator(heapArgs, JavascriptAsyncFunction::FromVar(function)->GetGeneratorVirtualScriptFunction(), prototype),
                stackArgs[0]);

        JavascriptPromise* promise = library->CreatePromise();
        JavascriptPromise::InitializePromise(promise, &resolve, &reject, scriptContext);

        try
        {
            CALL_FUNCTION(scriptContext->GetThreadContext(), executor, CallInfo(CallFlags_Value, 3), library->GetUndefined(), resolve, reject);
        }
        catch (const JavascriptException& err)
        {
            e = err.GetAndClear();
        }

        if (e != nullptr)
        {
            JavascriptPromise::TryRejectWithExceptionObject(e, reject, scriptContext);
        }

        return promise;
    }