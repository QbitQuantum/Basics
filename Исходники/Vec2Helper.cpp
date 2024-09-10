vector<Vec2WithId*> Vec2Helper::orderCW(vector<Vec2WithId*> points, Vec2f center) {
    for (unsigned int i=0; i<points.size(); i++) {
        Vec2f p = points[i]->vec-center;
        p.normalize();

        points[i]->vec = p;
    }

    std::sort(points.begin(), points.end(), compareAngle);
    return points;
}