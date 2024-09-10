bool VEF::isFaceInZone(Face f, int zid)
{

    Zone z = m_zones[zid];
    bool vA, vB, vC;

    vA = isVertexInZone(m_vertices[f.getA()], zid);
    vB = isVertexInZone(m_vertices[f.getB()], zid);
    vC = isVertexInZone(m_vertices[f.getC()], zid);

    return (vA && vB && vC);
}