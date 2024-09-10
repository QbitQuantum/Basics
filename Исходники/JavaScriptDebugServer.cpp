void JavaScriptDebugServer::removeBreakpoint(int sourceID, unsigned lineNumber)
{
    HashSet<unsigned>* lines = m_breakpoints.get(sourceID);
    if (!lines)
        return;

    lines->remove(lineNumber);

    if (!lines->isEmpty())
        return;

    m_breakpoints.remove(sourceID);
    delete lines;
}