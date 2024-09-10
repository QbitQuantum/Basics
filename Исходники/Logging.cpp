ScopeTrace::ScopeTrace(const char* pTraceFunction)
{
    if (g_loggerSingleton.IsTracingEnabled())
    {
        gTracerSingleton.EnterFunction(pTraceFunction);
        m_traceFunction = pTraceFunction;
    }
}