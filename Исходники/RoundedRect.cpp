void RoundedRect::Radii::includeLogicalEdges(const RoundedRect::Radii& edges, bool includeLogicalLeftEdge, bool includeLogicalRightEdge)
{
    if (includeLogicalLeftEdge) {
        m_bottomLeft = edges.bottomLeft();
        m_topLeft = edges.topLeft();
    }

    if (includeLogicalRightEdge) {
        m_topRight = edges.topRight();
        m_bottomRight = edges.bottomRight();
    }
}