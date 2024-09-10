 T boundary(const line<T>& o) const {
     if (a == o.a) return b > o.b ? inf : -inf;
     return div(o.b - b, a - o.a);
 }