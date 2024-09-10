bool SnapToLinesLayouter::isOverlapping() const
{
    IntRect cueBoxRect = m_cueBox.absoluteBoundingBoxRect();
    for (LayoutObject* box = m_cueBox.previousSibling(); box; box = box->previousSibling()) {
        IntRect boxRect = box->absoluteBoundingBoxRect();

        if (cueBoxRect.intersects(boxRect))
            return true;
    }

    if (cueBoxRect.intersects(m_controlsRect))
        return true;

    return false;
}