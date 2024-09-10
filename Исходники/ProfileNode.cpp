void ProfileNode::addChild(PassRefPtr<ProfileNode> prpChild)
{
    RefPtr<ProfileNode> child = prpChild;
    child->setParent(this);
    if (m_children.size())
        m_children.last()->setNextSibling(child.get());
    m_children.append(child.release());
}