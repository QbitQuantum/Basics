void reflect_ray(Point &dir, const Segment &mirror) {
    Point normal = (mirror.b - mirror.a);
    swap(normal.x, normal.y);
    normal.x *= -1;
    normal.normalize();
    
    long double dot = 2 * (dir ^ normal);
    dir.x -= dot * normal.x;
    dir.y -= dot * normal.y;
}