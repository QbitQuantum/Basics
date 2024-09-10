Point
MotionPlanner::nearest_env_point(const ExPolygonCollection &env, const Point &from, const Point &to) const
{
    /*  In order to ensure that the move between 'from' and the initial env point does
        not violate any of the configuration space boundaries, we limit our search to
        the points that satisfy this condition. */
    
    /*  Assume that this method is never called when 'env' contains 'from';
        so 'from' is either inside a hole or outside all contours */
    
    // get the points of the hole containing 'from', if any
    Points pp;
    for (ExPolygons::const_iterator ex = env.expolygons.begin(); ex != env.expolygons.end(); ++ex) {
        for (Polygons::const_iterator h = ex->holes.begin(); h != ex->holes.end(); ++h) {
            if (h->contains(from)) {
                pp = *h;
            }
        }
        if (!pp.empty()) break;
    }
    
    /*  If 'from' is not inside a hole, it's outside of all contours, so take all
        contours' points */
    if (pp.empty()) {
        for (ExPolygons::const_iterator ex = env.expolygons.begin(); ex != env.expolygons.end(); ++ex) {
            Points contour_pp = ex->contour;
            pp.insert(pp.end(), contour_pp.begin(), contour_pp.end());
        }
    }
    
    /*  Find the candidate result and check that it doesn't cross any boundary.
        (We could skip all of the above polygon finding logic and directly test all points
        in env, but this way we probably reduce complexity). */
    Polygons env_pp = env;
    while (pp.size() >= 2) {
        // find the point in pp that is closest to both 'from' and 'to'
        size_t result = from.nearest_waypoint_index(pp, to);
        
        if (intersects((Lines)Line(from, pp[result]), env_pp)) {
            // discard result
            pp.erase(pp.begin() + result);
        } else {
            return pp[result];
        }
    }
    
    // if we're here, return last point if any (better than nothing)
    if (!pp.empty()) return pp.front();
    
    // if we have no points at all, then we have an empty environment and we
    // make this method behave as a no-op (we shouldn't get here by the way)
    return from;
}