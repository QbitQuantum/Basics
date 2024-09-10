void UserActionElementSet::setFlags(Node* node, unsigned flags)
{
    if (!node->isElementNode())
        return;
    return setFlags(toElement(node), flags);
}