bool SFH_ClosedBSpline::intersects (BoxObj& userb, Graphic* gs) {
    PointObj po;
    const Coord *x, *y;
    int count = GetOriginal(x, y);
    Transformer* t = gs->GetTransformer();

    for (int i = 0; i < count; i++) {
	po._x = x[i];
	po._y = y[i];

        if (t != nil) {
            t->Transform(po._x, po._y);
        }
	if (userb.Contains(po)) {
            return true;
        }
    }
    return SF_ClosedBSpline::intersects(userb, gs);
}