bool CsgDisk::intersects(const Vec2f &vertice) const
{
    if(!intersectsBBox(vertice))
        return false;
    Vec2f transformedVertice = T_Inverted() * vertice;
    return transformedVertice.distance(Origin()) <= 0.5f;
}