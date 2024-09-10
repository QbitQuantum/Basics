GrFragmentProcessor* GrConvexPolyEffect::Create(GrPrimitiveEdgeType type, const SkPath& path,
                                                const SkVector* offset) {
    if (kHairlineAA_GrProcessorEdgeType == type) {
        return nullptr;
    }
    if (path.getSegmentMasks() != SkPath::kLine_SegmentMask ||
        !path.isConvex()) {
        return nullptr;
    }

    SkPathPriv::FirstDirection dir;
    // The only way this should fail is if the clip is effectively a infinitely thin line. In that
    // case nothing is inside the clip. It'd be nice to detect this at a higher level and either
    // skip the draw or omit the clip element.
    if (!SkPathPriv::CheapComputeFirstDirection(path, &dir)) {
        if (GrProcessorEdgeTypeIsInverseFill(type)) {
            return GrConstColorProcessor::Create(0xFFFFFFFF,
                                                 GrConstColorProcessor::kModulateRGBA_InputMode);
        }
        return GrConstColorProcessor::Create(0, GrConstColorProcessor::kIgnore_InputMode);
    }

    SkVector t;
    if (nullptr == offset) {
        t.set(0, 0);
    } else {
        t = *offset;
    }

    SkScalar        edges[3 * kMaxEdges];
    SkPoint         pts[4];
    SkPath::Verb    verb;
    SkPath::Iter    iter(path, true);

    // SkPath considers itself convex so long as there is a convex contour within it,
    // regardless of any degenerate contours such as a string of moveTos before it.
    // Iterate here to consume any degenerate contours and only process the points
    // on the actual convex contour.
    int n = 0;
    while ((verb = iter.next(pts, true, true)) != SkPath::kDone_Verb) {
        switch (verb) {
            case SkPath::kMove_Verb:
                SkASSERT(n == 0);
            case SkPath::kClose_Verb:
                break;
            case SkPath::kLine_Verb: {
                if (n >= kMaxEdges) {
                    return nullptr;
                }
                SkVector v = pts[1] - pts[0];
                v.normalize();
                if (SkPathPriv::kCCW_FirstDirection == dir) {
                    edges[3 * n] = v.fY;
                    edges[3 * n + 1] = -v.fX;
                } else {
                    edges[3 * n] = -v.fY;
                    edges[3 * n + 1] = v.fX;
                }
                SkPoint p = pts[1] + t;
                edges[3 * n + 2] = -(edges[3 * n] * p.fX + edges[3 * n + 1] * p.fY);
                ++n;
                break;
            }
            default:
                return nullptr;
        }
    }

    if (path.isInverseFillType()) {
        type = GrInvertProcessorEdgeType(type);
    }
    return Create(type, n, edges);
}