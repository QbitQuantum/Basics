double FacetSequence::distance(const FacetSequence & facetSeq) const {
    bool isPointThis = isPoint();
    bool isPointOther = facetSeq.isPoint();

    if (isPointThis && isPointOther) {
        Coordinate pt = pts->getAt(start);
        Coordinate seqPt = facetSeq.pts->getAt(facetSeq.start);
        return pt.distance(seqPt);

    } else if (isPointThis) {
        Coordinate pt = pts->getAt(start);
        return computePointLineDistance(pt, facetSeq);
    } else if (isPointOther) {
        Coordinate seqPt = facetSeq.pts->getAt(facetSeq.start);
        return computePointLineDistance(seqPt, *this);
    }

    return computeLineLineDistance(facetSeq);
}