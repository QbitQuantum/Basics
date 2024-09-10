box2d<T>::box2d(const box2d_type &rhs, const agg::trans_affine& tr)
{
    double x0 = rhs.minx_, y0 = rhs.miny_;
    double x1 = rhs.maxx_, y1 = rhs.miny_;
    double x2 = rhs.maxx_, y2 = rhs.maxy_;
    double x3 = rhs.minx_, y3 = rhs.maxy_;
    tr.transform(&x0, &y0);
    tr.transform(&x1, &y1);
    tr.transform(&x2, &y2);
    tr.transform(&x3, &y3);
    init(x0, y0, x2, y2);
    expand_to_include(x1, y1);
    expand_to_include(x3, y3);
}