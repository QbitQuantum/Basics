void AccessibilityMenuListPopup::childrenChanged()
{
    AXObjectCache* cache = axObjectCache();
    for (size_t i = m_children.size(); i > 0 ; --i) {
        AccessibilityObject* child = m_children[i - 1].get();
        if (child->actionElement() && !child->actionElement()->inRenderedDocument()) {
            child->detachFromParent();
            cache->remove(child->axObjectID());
        }
    }
    
    m_children.clear();
    m_haveChildren = false;
    addChildren();
}