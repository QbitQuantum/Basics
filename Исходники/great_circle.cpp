great_circle::arc great_circle::arc::shortest_path( const coordinates &c ) const
{
    Eigen::Vector3d cc(c.to_cartesian());
    if (angle() == 0) { return arc(cc, begin()); }
    if (has_inside(c)) { return arc(cc, cc); }

    Eigen::Vector3d n = end() - begin();
    Eigen::Vector3d p((n*(n.dot(cc - begin())))/n.dot(n) + begin());
    boost::optional< coordinates > t = intersection_with(arc(p, cc));
    if (! t)
    {
        arc a1(cc, begin());
        arc a2(cc, end());
        return a1.angle() < a2.angle() ? a1 : a2;
    }
    return arc(cc, *t);
}