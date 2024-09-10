void StyleElement::process(Element* e)
{
    if (!e || !e->inDocument())
        return;

    unsigned resultLength = 0;
    for (Node* c = e->firstChild(); c; c = c->nextSibling()) {
        if (isValidStyleChild(c)) {
            unsigned length = c->nodeValue().length();
            if (length > std::numeric_limits<unsigned>::max() - resultLength) {
                createSheet(e, m_startLineNumber, "");
                return;
            }
            resultLength += length;
        }
    }
    StringBuilder sheetText;
    sheetText.reserveCapacity(resultLength);

    for (Node* c = e->firstChild(); c; c = c->nextSibling()) {
        if (isValidStyleChild(c)) {
            sheetText.append(c->nodeValue());
        }
    }
    ASSERT(sheetText.length() == resultLength);

    createSheet(e, m_startLineNumber, sheetText.toString());
}