Steer
SteerAI::Flee(const Point& pt)
{
    Steer s;

    Point point = pt;
    point.Normalize();

    // approach
    if (point.z > 0.0f) {
        if (point.x > 0) s.yaw = -1.0f;
        else             s.yaw =  1.0f;
    }

    // flee
    else {
        s.yaw   = -point.x;
        s.pitch =  point.y;
    }

    return s;
}