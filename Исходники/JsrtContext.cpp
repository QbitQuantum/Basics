/* static */
bool JsrtContext::TrySetCurrent(JsrtContext * context)
{
    Assert(s_tlsSlot != TLS_OUT_OF_INDEXES);

    ThreadContext * threadContext;

    //We are not pinning the context after SetCurrentContext, so if the context is not pinned
    //it might be reclaimed half way during execution. In jsrtshell the runtime was optimized out
    //at time of JsrtContext::Run by the compiler.
    //The change is to pin the context at setconcurrentcontext, and unpin the previous one. In
    //JsDisposeRuntime we'll reject if current context is active, so that will make sure all
    //contexts are unpinned at time of JsDisposeRuntime.
    if (context != nullptr)
    {
        threadContext = context->GetScriptContext()->GetThreadContext();

        if (!ThreadContextTLSEntry::TrySetThreadContext(threadContext))
        {
            return false;
        }
        threadContext->GetRecycler()->RootAddRef((LPVOID)context);
    }
    else
    {
        if (!ThreadContextTLSEntry::ClearThreadContext(true))
        {
            return false;
        }
    }

    JsrtContext* originalContext = (JsrtContext*) TlsGetValue(s_tlsSlot);
    if (originalContext != nullptr)
    {
        originalContext->GetScriptContext()->GetRecycler()->RootRelease((LPVOID) originalContext);
    }

    TlsSetValue(s_tlsSlot, context);
    return true;
}