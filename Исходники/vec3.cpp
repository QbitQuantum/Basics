OpenSteer::Vec3
OpenSteer::findPerpendicularIn3d (const Vec3& direction)
{
    // to be filled in:
    Vec3 quasiPerp;  // a direction which is "almost perpendicular"
    Vec3 result;     // the computed perpendicular to be returned

    // three mutually perpendicular basis vectors
    const Vec3 i (1, 0, 0);
    const Vec3 j (0, 1, 0);
    const Vec3 k (0, 0, 1);

    // measure the projection of "direction" onto each of the axes
    const float id = i.dot (direction);
    const float jd = j.dot (direction);
    const float kd = k.dot (direction);

    // set quasiPerp to the basis which is least parallel to "direction"
    if ((id <= jd) && (id <= kd))
    {
        quasiPerp = i;               // projection onto i was the smallest
    }
    else
    {
        if ((jd <= id) && (jd <= kd))
            quasiPerp = j;           // projection onto j was the smallest
        else
            quasiPerp = k;           // projection onto k was the smallest
    }

    // return the cross product (direction x quasiPerp)
    // which is guaranteed to be perpendicular to both of them
    result.cross (direction, quasiPerp);
    return result;
}