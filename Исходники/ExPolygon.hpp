inline Polylines to_polylines(const ExPolygons &src)
{
    Polylines polylines;
    polylines.assign(number_polygons(src), Polyline());
    size_t idx = 0;
    for (ExPolygons::const_iterator it = src.begin(); it != src.end(); ++it) {
        Polyline &pl = polylines[idx ++];
        pl.points = it->contour.points;
        pl.points.push_back(pl.points.front());
        for (Polygons::const_iterator ith = it->holes.begin(); ith != it->holes.end(); ++ith) {
            Polyline &pl = polylines[idx ++];
            pl.points = ith->points;
            pl.points.push_back(ith->points.front());
        }
    }
    assert(idx == polylines.size());
    return polylines;
}