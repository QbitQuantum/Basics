void ILocalEntity::addChild(ILocalEntity * child)
{
    if (child != nullptr && child != this && !isChild(child))
    {
        m_children.push_front(child);
        child->setParent(this);
    }
}