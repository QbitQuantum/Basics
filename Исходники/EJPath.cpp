void EJPath::arcTo(float x1, float y1, float x2, float y2, float radius) {
    // Lifted from http://code.google.com/p/fxcanvas/
    // I have no idea what this code is doing, but it seems to work.

    // get untransformed currentPos
    EJVector2 cp = EJVector2ApplyTransform(currentPos, CGAffineTransformInvert(transform));

    float a1 = cp.y - y1;
    float b1 = cp.x - x1;
    float a2 = y2   - y1;
    float b2 = x2   - x1;
    float mm = fabsf(a1 * b2 - b1 * a2);

    if( mm < 1.0e-8 || radius == 0 ) {
        lineTo(x1, y1);
    }
    else {
        float dd = a1 * a1 + b1 * b1;
        float cc = a2 * a2 + b2 * b2;
        float tt = a1 * a2 + b1 * b2;
        float k1 = radius * sqrtf(dd) / mm;
        float k2 = radius * sqrtf(cc) / mm;
        float j1 = k1 * tt / dd;
        float j2 = k2 * tt / cc;
        float cx = k1 * b2 + k2 * b1;
        float cy = k1 * a2 + k2 * a1;
        float px = b1 * (k2 + j1);
        float py = a1 * (k2 + j1);
        float qx = b2 * (k1 + j2);
        float qy = a2 * (k1 + j2);
        float startAngle = atan2f(py - cy, px - cx);
        float endAngle = atan2f(qy - cy, qx - cx);

        arc(cx + x1, cy + y1, radius, startAngle, endAngle, (b1 * a2 > b2 * a1));
    }
}