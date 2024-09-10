bool BlockPainter::intersectsPaintRect(const PaintInfo& paintInfo, const LayoutPoint& paintOffset) const
{
    LayoutRect overflowRect = m_layoutBlock.visualOverflowRect();
    if (m_layoutBlock.hasOverflowModel() && m_layoutBlock.usesCompositedScrolling()) {
        overflowRect.unite(m_layoutBlock.layoutOverflowRect());
        overflowRect.move(-m_layoutBlock.scrolledContentOffset());
    }
    m_layoutBlock.flipForWritingMode(overflowRect);
    overflowRect.moveBy(paintOffset + m_layoutBlock.location());
    return (overflowRect.intersects(LayoutRect(paintInfo.rect)));
}