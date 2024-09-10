void RenderFrameSet::positionFramesWithFlattening()
{
    RenderBox* child = firstChildBox();
    if (!child)
        return;

    int rows = frameSetElement().totalRows();
    int cols = frameSetElement().totalCols();

    int borderThickness = frameSetElement().border();
    bool repaintNeeded = false;

    // calculate frameset height based on actual content height to eliminate scrolling
    bool out = false;
    for (int r = 0; r < rows && !out; r++) {
        int extra = 0;
        int height = m_rows.m_sizes[r];

        for (int c = 0; c < cols; c++) {
            IntRect oldFrameRect = pixelSnappedIntRect(child->frameRect());

            int width = m_cols.m_sizes[c];

            bool fixedWidth = frameSetElement().colLengths() && frameSetElement().colLengths()[c].isFixed();
            bool fixedHeight = frameSetElement().rowLengths() && frameSetElement().rowLengths()[r].isFixed();

            // has to be resized and itself resize its contents
            if (!fixedWidth)
                child->setWidth(width ? width + extra / (cols - c) : 0);
            else
                child->setWidth(width);
            child->setHeight(height);

            child->setNeedsLayout();

            if (child->isFrameSet())
                toRenderFrameSet(child)->layout();
            else
                toRenderFrame(child)->layoutWithFlattening(fixedWidth, fixedHeight);

            if (child->height() > m_rows.m_sizes[r])
                m_rows.m_sizes[r] = child->height();
            if (child->width() > m_cols.m_sizes[c])
                m_cols.m_sizes[c] = child->width();

            if (child->frameRect() != oldFrameRect)
                repaintNeeded = true;

            // difference between calculated frame width and the width it actually decides to have
            extra += width - m_cols.m_sizes[c];

            child = child->nextSiblingBox();
            if (!child) {
                out = true;
                break;
            }
        }
    }

    int xPos = 0;
    int yPos = 0;
    out = false;
    child = firstChildBox();
    for (int r = 0; r < rows && !out; r++) {
        xPos = 0;
        for (int c = 0; c < cols; c++) {
            // ensure the rows and columns are filled
            IntRect oldRect = pixelSnappedIntRect(child->frameRect());

            child->setLocation(IntPoint(xPos, yPos));
            child->setHeight(m_rows.m_sizes[r]);
            child->setWidth(m_cols.m_sizes[c]);

            if (child->frameRect() != oldRect) {
                repaintNeeded = true;

                // update to final size
                child->setNeedsLayout();
                if (child->isFrameSet())
                    toRenderFrameSet(child)->layout();
                else
                    toRenderFrame(child)->layoutWithFlattening(true, true);
            }

            xPos += m_cols.m_sizes[c] + borderThickness;
            child = child->nextSiblingBox();
            if (!child) {
                out = true;
                break;
            }
        }
        yPos += m_rows.m_sizes[r] + borderThickness;
    }

    setWidth(xPos - borderThickness);
    setHeight(yPos - borderThickness);

    if (repaintNeeded)
        repaint();

    // all the remaining frames are hidden to avoid ugly spurious unflowed frames
    for (; child; child = child->nextSiblingBox()) {
        child->setWidth(0);
        child->setHeight(0);
        child->clearNeedsLayout();
    }
}