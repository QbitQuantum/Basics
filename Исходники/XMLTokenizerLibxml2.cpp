void XMLTokenizer::endElementNs()
{
    if (m_parserStopped)
        return;

    if (m_parserPaused) {
        m_pendingCallbacks->appendEndElementNSCallback();
        return;
    }
    
    exitText();

    Node* n = m_currentNode;
    n->finishParsingChildren();

    if (m_scriptingPermission == FragmentScriptingNotAllowed && n->isElementNode() && toScriptElement(static_cast<Element*>(n))) {
        popCurrentNode();
        ExceptionCode ec;       
        n->remove(ec);
        return;
    }
    
    if (!n->isElementNode() || !m_view) {
        popCurrentNode();
        return;
    }

    Element* element = static_cast<Element*>(n);

    // The element's parent may have already been removed from document.
    // Parsing continues in this case, but scripts aren't executed.
    if (!element->inDocument()) {
        popCurrentNode();
        return;
    }

    ScriptElement* scriptElement = toScriptElement(element);
    if (!scriptElement) {
        popCurrentNode();
        return;
    }

    // Don't load external scripts for standalone documents (for now).
    ASSERT(!m_pendingScript);
    m_requestingScript = true;

#if ENABLE(XHTMLMP)
    if (!scriptElement->shouldExecuteAsJavaScript())
        m_doc->setShouldProcessNoscriptElement(true);
    else 
#endif
    {
        String scriptHref = scriptElement->sourceAttributeValue();
        if (!scriptHref.isEmpty()) {
            // we have a src attribute 
            String scriptCharset = scriptElement->scriptCharset();
            if (element->dispatchBeforeLoadEvent(scriptHref) &&
                (m_pendingScript = m_doc->docLoader()->requestScript(scriptHref, scriptCharset))) {
                m_scriptElement = element;
                m_pendingScript->addClient(this);

                // m_pendingScript will be 0 if script was already loaded and ref() executed it
                if (m_pendingScript)
                    pauseParsing();
            } else 
                m_scriptElement = 0;
        } else
            m_view->frame()->script()->executeScript(ScriptSourceCode(scriptElement->scriptContent(), m_doc->url(), m_scriptStartLine));
    }
    m_requestingScript = false;
    popCurrentNode();
}