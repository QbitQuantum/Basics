int FixedTableLayout::calcWidthArray(int)
{
    int usedWidth = 0;

    // iterate over all <col> elements
    unsigned nEffCols = m_table->numEffCols();
    m_width.resize(nEffCols);
    m_width.fill(Length(Auto));

    unsigned currentEffectiveColumn = 0;
    for (RenderTableCol* col = m_table->firstColumn(); col; col = col->nextColumn()) {
        col->computePreferredLogicalWidths();

        // Width specified by column-groups that have column child does not affect column width in fixed layout tables
        if (col->isTableColumnGroupWithColumnChildren())
            continue;

        Length colStyleLogicalWidth = col->style()->logicalWidth();
        int effectiveColWidth = 0;
        if (colStyleLogicalWidth.isFixed() && colStyleLogicalWidth.value() > 0)
            effectiveColWidth = colStyleLogicalWidth.value();

        unsigned span = col->span();
        while (span) {
            unsigned spanInCurrentEffectiveColumn;
            if (currentEffectiveColumn >= nEffCols) {
                m_table->appendColumn(span);
                nEffCols++;
                m_width.append(Length());
                spanInCurrentEffectiveColumn = span;
            } else {
                if (span < m_table->spanOfEffCol(currentEffectiveColumn)) {
                    m_table->splitColumn(currentEffectiveColumn, span);
                    nEffCols++;
                    m_width.append(Length());
                }
                spanInCurrentEffectiveColumn = m_table->spanOfEffCol(currentEffectiveColumn);
            }
            if ((colStyleLogicalWidth.isFixed() || colStyleLogicalWidth.isPercent()) && colStyleLogicalWidth.isPositive()) {
                m_width[currentEffectiveColumn] = colStyleLogicalWidth;
                m_width[currentEffectiveColumn] *= spanInCurrentEffectiveColumn;
                usedWidth += effectiveColWidth * spanInCurrentEffectiveColumn;
            }
            span -= spanInCurrentEffectiveColumn;
            currentEffectiveColumn++;
        }
    }

    // Iterate over the first row in case some are unspecified.
    RenderTableSection* section = m_table->topNonEmptySection();
    if (!section)
        return usedWidth;

    unsigned currentColumn = 0;

    RenderObject* firstRow = section->firstChild();
    for (RenderObject* child = firstRow->firstChild(); child; child = child->nextSibling()) {
        if (!child->isTableCell())
            continue;

        RenderTableCell* cell = toRenderTableCell(child);
        if (cell->preferredLogicalWidthsDirty())
            cell->computePreferredLogicalWidths();

        Length logicalWidth = cell->styleOrColLogicalWidth();
        unsigned span = cell->colSpan();
        int fixedBorderBoxLogicalWidth = 0;
        if (logicalWidth.isFixed() && logicalWidth.isPositive()) {
            fixedBorderBoxLogicalWidth = cell->adjustBorderBoxLogicalWidthForBoxSizing(logicalWidth.value());
            logicalWidth.setValue(fixedBorderBoxLogicalWidth);
        }

        unsigned usedSpan = 0;
        while (usedSpan < span && currentColumn < nEffCols) {
            float eSpan = m_table->spanOfEffCol(currentColumn);
            // Only set if no col element has already set it.
            if (m_width[currentColumn].isAuto() && logicalWidth.type() != Auto) {
                m_width[currentColumn] = logicalWidth;
                m_width[currentColumn] *= eSpan / span;
                usedWidth += fixedBorderBoxLogicalWidth * eSpan / span;
            }
            usedSpan += eSpan;
            ++currentColumn;
        }
    }

    return usedWidth;
}