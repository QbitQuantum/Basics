static void scanConvert(const WFMath::Polygon<2>& inPoly, Surface& sf)
{
    if (!inPoly.isValid()) return;
    
    std::list<Edge> pending;
    std::vector<Edge> active;

    Point2 lastPt = inPoly.getCorner(inPoly.numCorners() - 1);
    for (std::size_t p=0; p < inPoly.numCorners(); ++p) {
        Point2 curPt = inPoly.getCorner(p);
        
        // skip horizontal edges
        if (curPt.y() != lastPt.y())
            pending.emplace_back(lastPt, curPt);
        
        lastPt = curPt;
    }
    
    if (pending.empty()) return;
    
    // sort edges by starting (lowest) z value
    pending.sort();
    active.push_back(pending.front());
    pending.pop_front();
    
    // advance to the row of the first z value, and ensure z sits in the
    // middle of sample rows - we do this by offseting by 1/2 a row height
    // if you don't do this, you'll find alternating rows are over/under
    // sampled, producing a charming striped effect.
    WFMath::CoordType z = std::floor(active.front().start().y()) + ROW_HEIGHT * 0.5f;
    
    for (; !pending.empty() || !active.empty();  z += ROW_HEIGHT)
    {
        while (!pending.empty() && (pending.front().start().y() <= z)) {
            active.push_back(pending.front());
            pending.pop_front();
        }
        
        // sort by x value - note active will be close to sorted anyway
        std::sort(active.begin(), active.end(), EdgeAtZ(z));
        
        // delete finished edges
        for (unsigned int i=0; i< active.size(); ) {
            if (active[i].end().y() <= z)
                active.erase(active.begin() + i);
            else
                ++i;
        }
        
        // draw pairs of active edges
        for (unsigned int i=1; i < active.size(); i += 2)
            span(sf, z, active[i - 1].xValueAtZ(z), active[i].xValueAtZ(z));
    } // of active edges loop
}