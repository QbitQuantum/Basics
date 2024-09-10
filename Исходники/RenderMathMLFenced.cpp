void RenderMathMLFenced::updateFromElement()
{
    const auto& fenced = element();
 
    // The open operator defaults to a left parenthesis.
    AtomicString open = fenced.fastGetAttribute(MathMLNames::openAttr);
    m_open = open.isNull() ? gOpeningBraceChar : open;

    // The close operator defaults to a right parenthesis.
    AtomicString close = fenced.fastGetAttribute(MathMLNames::closeAttr);
    m_close = close.isNull() ? gClosingBraceChar : close;

    AtomicString separators = fenced.fastGetAttribute(MathMLNames::separatorsAttr);
    if (!separators.isNull()) {
        StringBuilder characters;
        for (unsigned int i = 0; i < separators.length(); i++) {
            if (!isSpaceOrNewline(separators[i]))
                characters.append(separators[i]);
        }
        m_separators = !characters.length() ? 0 : characters.toString().impl();
    } else {
        // The separator defaults to a single comma.
        m_separators = StringImpl::create(",");
    }
    
    if (isEmpty())
        makeFences();
    else {
        // FIXME: The mfenced element fails to update dynamically when its open, close and separators attributes are changed (https://bugs.webkit.org/show_bug.cgi?id=57696).
        toRenderMathMLOperator(firstChild())->updateTokenContent(m_open);
        m_closeFenceRenderer->updateTokenContent(m_close);
    }
}