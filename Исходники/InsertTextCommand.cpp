Position InsertTextCommand::insertTab(const Position& pos)
{
    Position insertPos = VisiblePosition(pos, DOWNSTREAM).deepEquivalent();
        
    Node *node = insertPos.node();
    unsigned int offset = insertPos.offset();

    // keep tabs coalesced in tab span
    if (isTabSpanTextNode(node)) {
        insertTextIntoNode(static_cast<Text *>(node), offset, "\t");
        return Position(node, offset + 1);
    }
    
    // create new tab span
    RefPtr<Element> spanNode = createTabSpanElement(document());
    
    // place it
    if (!node->isTextNode()) {
        insertNodeAt(spanNode.get(), node, offset);
    } else {
        Text *textNode = static_cast<Text *>(node);
        if (offset >= textNode->length()) {
            insertNodeAfter(spanNode.get(), textNode);
        } else {
            // split node to make room for the span
            // NOTE: splitTextNode uses textNode for the
            // second node in the split, so we need to
            // insert the span before it.
            if (offset > 0)
                splitTextNode(textNode, offset);
            insertNodeBefore(spanNode.get(), textNode);
        }
    }
    
    // return the position following the new tab
    return Position(spanNode->lastChild(), spanNode->lastChild()->caretMaxOffset());
}