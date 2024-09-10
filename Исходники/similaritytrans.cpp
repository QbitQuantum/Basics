void SimilarityTrans::setTransformByAlign(const ShapeVec &x, const ShapeVec &xp) {
    int nP = x.rows / 2;
    a = xp.dot(x) / x.dot(x);
    b = 0;
    for (int i=0; i<nP; i++)
        b += x.X(i) * xp.Y(i) - x.Y(i)*xp.X(i);
    b /= x.dot(x);
    double xxm, xym;
    xxm = x.getXMean();
    xym = x.getYMean();
    Xt = -a * xxm + b * xym + xp.getXMean();
    Yt = -b * xxm - a * xym + xp.getYMean();
}