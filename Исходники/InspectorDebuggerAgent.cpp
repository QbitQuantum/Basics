void InspectorDebuggerAgent::removeBreakpoint(ErrorString*, const String& breakpointId)
{
    RefPtr<JSONObject> breakpointsCookie = m_state->getObject(DebuggerAgentState::javaScriptBreakpoints);
    JSONObject::iterator it = breakpointsCookie->find(breakpointId);
    bool isAntibreakpoint = false;
    if (it != breakpointsCookie->end()) {
        RefPtr<JSONObject> breakpointObject = it->value->asObject();
        breakpointObject->getBoolean(DebuggerAgentState::isAnti, &isAntibreakpoint);
        breakpointsCookie->remove(breakpointId);
        m_state->setObject(DebuggerAgentState::javaScriptBreakpoints, breakpointsCookie);
    }

    if (!isAntibreakpoint)
        removeBreakpoint(breakpointId);
}