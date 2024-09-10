void CSSVariablesDeclaration::addParsedVariable(const String& variableName, PassRefPtr<StyleBase> variableValue, bool updateNamesList)
{
    variableValue->setParent(this); // Needed to connect variables that are CSSMutableStyleDeclarations, since the parent couldn't be set until now.

    // Don't leak duplicates.  For multiple variables with the same name, the last one
    // declared will win.
    StyleBase* current = m_variablesMap.take(variableName).get();
    if (!current && updateNamesList)
        m_variableNames.append(variableName);
    m_variablesMap.set(variableName, variableValue);

    // FIXME: Communicate this change so the document will update.
}