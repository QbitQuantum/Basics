bool EllipsisBox::nodeAtPoint(const HitTestRequest& request, HitTestResult& result, int x, int y, int tx, int ty)
{
    tx += m_x;
    ty += m_y;

    // Hit test the markup box.
    if (m_markupBox) {
        RenderStyle* style = m_renderer->style(m_firstLine);
        int mtx = tx + m_width - m_markupBox->x();
        int mty = ty + style->font().ascent() - (m_markupBox->y() + m_markupBox->renderer()->style(m_firstLine)->font().ascent());
        if (m_markupBox->nodeAtPoint(request, result, x, y, mtx, mty)) {
            renderer()->updateHitTestResult(result, IntPoint(x - mtx, y - mty));
            return true;
        }
    }

    IntRect boundsRect = IntRect(tx, ty, m_width, m_height);
    if (visibleToHitTesting() && boundsRect.intersects(result.rectFromPoint(x, y))) {
        renderer()->updateHitTestResult(result, IntPoint(x - tx, y - ty));
        if (!result.addNodeToRectBasedTestResult(renderer()->node(), x, y, boundsRect))
            return true;
    }

    return false;
}