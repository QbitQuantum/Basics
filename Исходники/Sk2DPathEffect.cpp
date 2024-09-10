bool Sk2DPathEffect::filterPath(SkPath* dst, const SkPath& src, SkStrokeRec*) {
    if (!fMatrixIsInvertible) {
        return false;
    }

    SkPath  tmp;
    SkIRect ir;

    src.transform(fInverse, &tmp);
    tmp.getBounds().round(&ir);
    if (!ir.isEmpty()) {
        this->begin(ir, dst);

        SkRegion rgn;
        rgn.setPath(tmp, SkRegion(ir));
        SkRegion::Iterator iter(rgn);
        for (; !iter.done(); iter.next()) {
            const SkIRect& rect = iter.rect();
            for (int y = rect.fTop; y < rect.fBottom; ++y) {
                this->nextSpan(rect.fLeft, y, rect.width(), dst);
            }
        }

        this->end(dst);
    }
    return true;
}