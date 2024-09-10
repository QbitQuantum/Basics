ll Area(const Point &a, const Point &b, const Point &c){
    return abs(a.Cross(b) + b.Cross(c) + c.Cross(a));
}