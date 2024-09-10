void ScrollingStateNode::appendChild(PassOwnPtr<ScrollingStateNode> childNode)
{
    childNode->setParent(this);

    if (!m_children)
        m_children = adoptPtr(new Vector<OwnPtr<ScrollingStateNode> >);

    m_children->append(childNode);
}