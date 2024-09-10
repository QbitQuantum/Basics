void Attr::createTextChild()
{
    ASSERT(refCount());
    if (!m_attribute->value().isEmpty()) {
        RefPtr<Text> textNode = document()->createTextNode(m_attribute->value().string());

        // This does everything appendChild() would do in this situation (assuming m_ignoreChildrenChanged was set),
        // but much more efficiently.
        textNode->setParent(this);
        setFirstChild(textNode.get());
        setLastChild(textNode.get());
    }
}