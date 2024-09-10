void CScript_EventPseudoModel::Script_EventPseudoModel_Emit(
    CFXJSE_Arguments* pArguments) {
    IXFA_ScriptContext* pScriptContext = m_pDocument->GetScriptContext();
    if (!pScriptContext) {
        return;
    }
    CXFA_EventParam* pEventParam = pScriptContext->GetEventParam();
    if (!pEventParam) {
        return;
    }
    IXFA_Notify* pNotify = m_pDocument->GetParser()->GetNotify();
    if (!pNotify) {
        return;
    }
    IXFA_WidgetHandler* pWidgetHandler = pNotify->GetWidgetHandler();
    if (!pWidgetHandler) {
        return;
    }
    pWidgetHandler->ProcessEvent(pEventParam->m_pTarget, pEventParam);
}