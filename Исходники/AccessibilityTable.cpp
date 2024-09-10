void AccessibilityTable::addChildren()
{
    if (!isAccessibilityTable()) {
        AccessibilityRenderObject::addChildren();
        return;
    }
    
    ASSERT(!m_haveChildren); 
    
    m_haveChildren = true;
    if (!m_renderer || !m_renderer->isTable())
        return;
    
    RenderTable* table = toRenderTable(m_renderer);
    AXObjectCache* axCache = m_renderer->document()->axObjectCache();

    // go through all the available sections to pull out the rows
    // and add them as children
    // FIXME: This will skip a table with just a tfoot. Should fix by using RenderTable::topSection.
    RenderTableSection* tableSection = table->header();
    if (!tableSection)
        tableSection = table->firstBody();
    
    if (!tableSection)
        return;
    
    RenderTableSection* initialTableSection = tableSection;
    
    while (tableSection) {
        
        HashSet<AccessibilityObject*> appendedRows;

        unsigned numRows = tableSection->numRows();
        unsigned numCols = tableSection->numColumns();
        for (unsigned rowIndex = 0; rowIndex < numRows; ++rowIndex) {
            for (unsigned colIndex = 0; colIndex < numCols; ++colIndex) {
                
                RenderTableCell* cell = tableSection->primaryCellAt(rowIndex, colIndex);
                if (!cell)
                    continue;
                
                AccessibilityObject* rowObject = axCache->getOrCreate(cell->parent());
                if (!rowObject->isTableRow())
                    continue;
                
                AccessibilityTableRow* row = static_cast<AccessibilityTableRow*>(rowObject);
                // we need to check every cell for a new row, because cell spans
                // can cause us to mess rows if we just check the first column
                if (appendedRows.contains(row))
                    continue;
                
                row->setRowIndex((int)m_rows.size());        
                m_rows.append(row);
                if (!row->accessibilityIsIgnored())
                    m_children.append(row);
#if PLATFORM(GTK)
                else
                    m_children.append(row->children());
#endif
                appendedRows.add(row);
            }
        }
        
        tableSection = table->sectionBelow(tableSection, SkipEmptySections);
    }
    
    // make the columns based on the number of columns in the first body
    unsigned length = initialTableSection->numColumns();
    for (unsigned i = 0; i < length; ++i) {
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