void transformDistributions(
    Vector3fVector& means,
    Matrix3fVector& covariances,
    const AffineTransform& transform)
{
    Matrix3f R = transform.rotation();
    Vector3f t = transform.translation();
    Matrix3f R_T = R.transpose();

    unsigned int size = means.size();
    for(unsigned int i = 0; i < size; ++i)
    {
        Vector3f& m = means[i];
        Matrix3f& c = covariances[i];
        m = R * m + t;
        c = R * c * R_T;
    }
}