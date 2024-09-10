Quaternion UnpackQuaternionFromFloat3(float x, float y, float z)
{
    if (_isnan(x) || _isnan(y) || _isnan(z) || !_finite(x) || !_finite(y) || !_finite(z))
        return Quaternion(0, 0, 0, 1.f);

    float sq = x*x+y*y+z*z;
    // If the inputted coordinates are already too large in magnitude, renormalize the inputs and just set w = 0.
    // It can happen in two cases: Either float imprecision gave us a bit too high values, so setting w=0 is the proper action,
    // or then server sent us values that are bad to begin with. Anything is incorrect in this case, but to preserve at least
    // some sensibility in computations, renormalize the components and set w=0.
    if (sq >= 1.f) 
    {
        float invNorm = 1.f / sqrt(sq);
        return Quaternion(x * invNorm, y * invNorm, z * invNorm, 0.f);
    }
    float w = sqrt(1.f - sq);
    return Quaternion(x, y, z, w);
}