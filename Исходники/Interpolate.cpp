Quaternion catmullRomInterpolate(
    const Quaternion& q00, const Quaternion& q01, const Quaternion& q02, const Quaternion& q03, 
    double t)
{
    // From method CatmullQuat(...) on page 449 of Visualizing Quaternions
    Quaternion q10 = q00.slerp(q01, t+1.0);
    Quaternion q11 = q01.slerp(q02, t+0.0);
    Quaternion q12 = q02.slerp(q03, t-1.0);
    Quaternion q20 = q10.slerp(q11, (t+1.0)/2.0);
    Quaternion q21 = q11.slerp(q12, t/2.0);
    return q20.slerp(q21, t);
}