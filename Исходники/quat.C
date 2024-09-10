void Squad (Quaternion* res, float t, Quaternion* p,
    Quaternion* a, Quaternion* b, Quaternion* q)
{
   Quaternion q1, q2;
   Slerp(&q1, t, p, q);
   Slerp(&q2, t, a, b);
   Slerp(res, 2 * t * (1 - t), &q1, &q2);
}