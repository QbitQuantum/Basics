double distance(Point2f aPoint, Vector2d aVector, Point2i startPoint)
{
    Vector2d v = aVector;
    Vector2d w(aPoint.x - startPoint.x, aPoint.y - startPoint.y);

    double c1 = v.dot(w);
    double c2 = v.dot(v);
    
    if (c1 <= 0){
        Point2d tmp;
        tmp.x = startPoint.x;
        tmp.y = startPoint.y;
        return distance(aPoint, tmp);
    }
    if (c2 <= 0){
        Point2d endPoint;
        endPoint.x = startPoint.x + (float) aVector[0];
        endPoint.y = startPoint.y + (float) aVector[1];

        return distance(aPoint, endPoint);
    }

    double b = c1 / c2;

    Point2d pb(startPoint.x + b * aVector[0], startPoint.y + b * aVector[1]);

    return distance(aPoint, pb);
}