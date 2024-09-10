int contains(VP ps, CP q) {
    int n = ps.size();
    int res = -1;
    for (int i = 0; i < n; i++) {
        Point a = ps[i] - q, b = ps[(i + 1) % n] - q;
        if (a.y > b.y) {
            Point t = a; a = b; b = t;
        }
        if (a.y < eps && b.y > eps && a.det(b) > eps) {
            res = -res;
        }
        if (abs(a.det(b)) < eps && a.dot(b) < eps) {
            return 0;
        }
    }
    return res;
}