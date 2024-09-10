WFMath::Polygon<2> sutherlandHodgmanKernel(const WFMath::Polygon<2>& inpoly, Clip clipper)
{
    WFMath::Polygon<2> outpoly;
    
    if (!inpoly.isValid()) return inpoly;
    std::size_t points = inpoly.numCorners();
    if (points < 3) return outpoly; // i.e an invalid result
    
    Point2 lastPt = inpoly.getCorner(points - 1);
    bool lastInside = clipper.inside(lastPt);
    
    for (std::size_t p = 0; p < points; ++p) {
    
        Point2 curPt = inpoly.getCorner(p);
        bool inside = clipper.inside(curPt);
        
        if (lastInside) {
            if (inside) {
                // emit curPt
                outpoly.addCorner(outpoly.numCorners(), curPt);
            } else {
                // emit intersection of edge with clip line
                outpoly.addCorner(outpoly.numCorners(), clipper.clip(lastPt, curPt));
            }
        } else {
            if (inside) {
                // emit both
                outpoly.addCorner(outpoly.numCorners(), clipper.clip(lastPt, curPt));
                outpoly.addCorner(outpoly.numCorners(), curPt);
            } else {
                // don't emit anything
            }
        } // last was outside
        
        lastPt = curPt;
        lastInside = inside;
    }
    
    return outpoly;
}