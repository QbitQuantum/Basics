bool WallEdge::Event::operator < (Event const &other) const
{
    return distance() < other.distance();
}