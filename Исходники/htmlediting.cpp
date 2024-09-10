bool lineBreakExistsAtPosition(const Position& position)
{
    if (position.isNull())
        return false;
    
    if (position.anchorNode()->hasTagName(brTag) && position.atFirstEditingPositionForNode())
        return true;
    
    if (!position.anchorNode()->isTextNode() || !position.anchorNode()->renderer()->style()->preserveNewline())
        return false;
    
    Text* textNode = static_cast<Text*>(position.anchorNode());
    unsigned offset = position.offsetInContainerNode();
    return offset < textNode->length() && textNode->data()[offset] == '\n';
}