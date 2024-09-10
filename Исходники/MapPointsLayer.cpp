void MapPointsLayer::onViewChanged(const Coordinate& a, const Coordinate& b)
{
    if(m_hasActivePoint)
    {
        // don't draw points
        return;
    }
    
    // TODO: update point on demand every half a second or so
    // will not significantly affect UX but will improve performance
    // Don't forget to resize all children of m_points
    
    Coordinate center = (a + b)/2;
    float radius = center.distance(a);
    std::list<MapPoint*> list;
    MapViewLayer::Context.PointsLoader->findAllPointsInRadius(center, radius, list);
    
    m_points->removeAllChildren();
    for(auto p : list)
    {
        addPoint(p);
    }
}