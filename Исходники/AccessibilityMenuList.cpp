void AccessibilityMenuList::addChildren()
{
    m_haveChildren = true;

    AXObjectCache* cache = m_renderer->document()->axObjectCache();

    AccessibilityObject* list = cache->getOrCreate(MenuListPopupRole);
    if (!list)
        return;

    if (list->accessibilityPlatformIncludesObject() == IgnoreObject) {
        cache->remove(list->axObjectID());
        return;
    }

    static_cast<AccessibilityMenuListPopup*>(list)->setMenuList(this);
    m_children.append(list);

    list->addChildren();
}