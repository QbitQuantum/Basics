int main() {
    int64_t n, x0, y0;
    cin >> n >> x0 >> y0;
    Point p = {x0, y0};
    Segment ray = {p, {inf, y0 + 1}};

    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        Point p;
        cin >> p.x >> p.y;
        points[i] = p;
    }
    int count = 0;
    bool onBound = false;
    for (int i = 0; i < n; i++) {
        Segment s = {points[i], points[(i + 1) % n]};
        if (s.contains(p)) {
            onBound = true;
            break;
        }
        if (ray.intersects(s)) {
            count++;
        }
    }
    cout << (onBound || count % 2 == 1 ? "YES" : "NO") << endl;

    return 0;
}