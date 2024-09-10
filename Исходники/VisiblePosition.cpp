UChar32 VisiblePosition::characterAfter() const
{
    // We canonicalize to the first of two equivalent candidates, but the second of the two candidates
    // is the one that will be inside the text node containing the character after this visible position.
    Position pos = m_deepPosition.downstream();
    Node* node = pos.containerNode();
    if (!node || !node->isTextNode() || pos.anchorType() == Position::PositionIsAfterAnchor)
        return 0;
    ASSERT(pos.anchorType() == Position::PositionIsBeforeAnchor || pos.anchorType() == Position::PositionIsOffsetInAnchor);
    Text* textNode = static_cast<Text*>(pos.containerNode());
    unsigned offset = pos.anchorType() == Position::PositionIsOffsetInAnchor ? pos.offsetInContainerNode() : 0;
    unsigned length = textNode->length();
    if (offset >= length)
        return 0;

    UChar32 ch;
    const UChar* characters = textNode->data().characters();
    U16_NEXT(characters, offset, length, ch);
    return ch;
}