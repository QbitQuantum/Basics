bool SkStrokeRec::applyToPath(SkPath* dst, const SkPath& src) const {
    if (fWidth <= 0) {  // hairline or fill
        return false;
    }

    SkStroke stroker;
    stroker.setCap(fCap);
    stroker.setJoin(fJoin);
    stroker.setMiterLimit(fMiterLimit);
    stroker.setWidth(fWidth);
    stroker.setDoFill(fStrokeAndFill);
#if QUAD_STROKE_APPROXIMATION
    stroker.setError(1);
#endif
    stroker.strokePath(src, dst);
    return true;
}