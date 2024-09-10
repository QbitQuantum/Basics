static void createStar(SkPath& path, SkScalar innerRadius, SkScalar outerRadius, 
        SkScalar startAngle, int points, SkPoint center) {
    SkScalar angle = startAngle;
    for (int index = 0; index < points * 2; ++index) {
        SkScalar radius = index & 1 ? outerRadius : innerRadius;
        SkScalar x = radius * cos(angle);
        SkScalar y = radius * sin(angle);
        x += center.fX;
        y += center.fY;
        if (index == 0) {
            path.moveTo(x, y);
        } else {
            path.lineTo(x, y);
        }
        angle += 3.1415f / points;
    }
    path.close();
}