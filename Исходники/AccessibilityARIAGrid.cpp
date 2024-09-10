void AccessibilityARIAGrid::addChildren()
{
    ASSERT(!m_haveChildren); 
    
    if (!isAccessibilityTable()) {
        AccessibilityRenderObject::addChildren();
        return;
    }
    
    m_haveChildren = true;
    if (!m_renderer)
        return;
    
    AXObjectCache* axCache = m_renderer->document()->axObjectCache();
    
    // add only rows that are labeled as aria rows
    HashSet<AccessibilityObject*> appendedRows;
    unsigned columnCount = 0;
    for (RefPtr<AccessibilityObject> child = firstChild(); child; child = child->nextSibling()) {

        if (!addTableCellChild(child.get(), appendedRows, columnCount)) {
            
            // in case the render tree doesn't match the expected ARIA hierarchy, look at the children
            if (!child->hasChildren())
                child->addChildren();

            // The children of this non-row will contain all non-ignored elements (recursing to find them). 
            // This allows the table to dive arbitrarily deep to find the rows.
            AccessibilityChildrenVector children = child->children();
            size_t length = children.size();
            for (size_t i = 0; i < length; ++i)
                addTableCellChild(children[i].get(), appendedRows, columnCount);
        }
    }
    
    // make the columns based on the number of columns in the first body
    for (unsigned i = 0; i < columnCount; ++i) {
        AccessibilityTableColumn* column = static_cast<AccessibilityTableColumn*>(axCache->getOrCreate(ColumnRole));
        column->setColumnIndex((int)i);
        column->setParent(this);
        m_columns.append(column);
        if (!column->accessibilityIsIgnored())
            m_children.append(column);
    }
    
    AccessibilityObject* headerContainerObject = headerContainer();
    if (headerContainerObject && !headerContainerObject->accessibilityIsIgnored())
        m_children.append(headerContainerObject);
}