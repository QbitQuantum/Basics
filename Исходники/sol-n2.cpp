void compute_convex_hull(vector<PI>& P) {
    vector<PI> H;
    FORE(p, P) {
        while (SIZE(H) >= 2 && !ccw(H[SIZE(H) - 2], H[SIZE(H) - 1], *p))
            H.pop_back();
        H.push_back(*p);
    }
    P.swap(H);
}