inline Quaternion<T> Squad(const Quaternion<T>& p, const Quaternion<T>& a, const Quaternion<T>& b, const Quaternion<T>& q, const T& time)
{
    Quaternion<T> qa = Slerp(p,q,time,0);
    Quaternion<T> qb = Slerp(a,b,time,0);
    T qtime = 2 * time * (1 - time);
    return Slerp(qa,qb,qtime,0);
}