void XmlElement::setText(const string& text) {
    assert(doc != NULL && "Attempt to create text on a root node");
    DOMNode* first = base->getFirstChild();
    bool found = false;
    while(first && !found) {
        if (first->getNodeType() == 3) {
            first->setTextContent(toUnicode(text));
            found = true;
        }
        first = first->getPreviousSibling();
    }
    if (!found) {
        DOMText* textNode = doc->createTextNode(toUnicode(text));
        base->appendChild(textNode);
    }
}