void WMLPElement::insertedIntoDocument()
{
    WMLElement::insertedIntoDocument();

    // If not explicitly specified, the linewrap mode is identical to 
    // the line-wrap mode of the previous paragraph in the text flow of
    // a card. The default mode for the first paragraph in a card is wrap.
    if (!m_mode.isEmpty())
        return;

    RefPtr<NodeList> nodeList = document()->getElementsByTagName("p");
    if (!nodeList)
        return;

    unsigned length = nodeList->length();
    if (length < 2)
        return;

    // Assure we're the last inserted paragraph element
    // This only works while parsing, otherwhise this statement is never true.
    if (nodeList->item(length - 1) != this)
        return;

    WMLPElement* lastParagraph = static_cast<WMLPElement*>(nodeList->item(length - 2));
    ASSERT(lastParagraph);

    String lastMode = lastParagraph->getAttribute(modeAttr);
    if (lastMode.isEmpty() || lastMode == "wrap") // Default value, do nothing.
        return;

    setAttribute(modeAttr, lastMode);
}