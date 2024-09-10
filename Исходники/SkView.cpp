bool SkView::globalToLocal(SkScalar x, SkScalar y, SkPoint* local) const {
    if (local) {
        SkMatrix m;
        this->localToGlobal(&m);
        if (!m.invert(&m)) {
            return false;
        }
        SkPoint p;
        m.mapXY(x, y, &p);
        local->set(p.fX, p.fY);
    }

    return true;
}