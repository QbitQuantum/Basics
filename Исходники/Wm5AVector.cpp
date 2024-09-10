//----------------------------------------------------------------------------
void AVector::Orthonormalize (AVector& vec0, AVector& vec1, AVector& vec2)
{
    // If the input vectors are v0, v1, and v2, then the Gram-Schmidt
    // orthonormalization produces vectors u0, u1, and u2 as follows,
    //
    //   u0 = v0/|v0|
    //   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
    //   u2 = (v2-(u0*v2)u0-(u1*v2)u1)/|v2-(u0*v2)u0-(u1*v2)u1|
    //
    // where |A| indicates length of vector A and A*B indicates dot
    // product of vectors A and B.

    // Compute u0.
    vec0.Normalize();

    // Compute u1.
    float dot0 = vec0.Dot(vec1);
    vec1 -= dot0*vec0;
    vec1.Normalize();

    // Compute u2.
    float dot1 = vec1.Dot(vec2);
    dot0 = vec0.Dot(vec2);
    vec2 -= dot0*vec0 + dot1*vec1;
    vec2.Normalize();
}