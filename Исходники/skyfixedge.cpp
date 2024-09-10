bool SkyFixEdge::Event::operator < (Event const &other) const
{
    return d->distance < other.distance();
}