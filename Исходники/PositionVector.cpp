std::vector<SUMOReal>
PositionVector::distances(const PositionVector& s, bool perpendicular) const {
    std::vector<SUMOReal> ret;
    const_iterator i;
    for (i = begin(); i != end(); i++) {
        const SUMOReal dist = s.distance(*i, perpendicular);
        if (dist != GeomHelper::INVALID_OFFSET) {
            ret.push_back(dist);
        }
    }
    for (i = s.begin(); i != s.end(); i++) {
        const SUMOReal dist = distance(*i, perpendicular);
        if (dist != GeomHelper::INVALID_OFFSET) {
            ret.push_back(dist);
        }
    }
    return ret;
}