Quaternion::Quaternion(Vector axis, float angle)
{
    axis.Normalize();
    angle = angle * PI / 180;
    r = cos(angle);
    i = sin(angle)*axis.x;
    j = sin(angle)*axis.y;
    k = sin(angle)*axis.z;
}