Edges edges(Path const &p, Crossings const &cr, unsigned ix) {
    Edges ret = Edges();
    EndPoint prev;
    for(unsigned i = 0; i <= cr.size(); i++) {
        double t = cr[i == cr.size() ? 0 : i].getTime(ix);
        Point pnt = p.pointAt(t);
        Point normal = p.pointAt(t+0.01) - pnt;
        normal.normalize();
        std::cout << pnt << "\n";
        EndPoint cur(pnt, normal, t);
        if(i == 0) { prev = cur; continue; }
        ret.push_back(Edge(prev, cur, ix, false));
        ret.push_back(Edge(prev, cur, ix, true));
        prev = cur;
    }
    return ret;
}