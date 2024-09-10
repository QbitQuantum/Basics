bool SkWindow::handleInval(const SkRect* localR) {
    SkIRect ir;

    if (localR) {
        SkRect devR;
        SkMatrix inverse;
        if (!fMatrix.invert(&inverse)) {
            return false;
        }
        fMatrix.mapRect(&devR, *localR);
        devR.round(&ir);
    } else {
        ir.set(0, 0,
               SkScalarRoundToInt(this->width()),
               SkScalarRoundToInt(this->height()));
    }
    fDirtyRgn.op(ir, SkRegion::kUnion_Op);

    this->onHandleInval(ir);
    return true;
}