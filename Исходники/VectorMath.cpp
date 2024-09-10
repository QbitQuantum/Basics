const Matrix3d VectorMath::TMatrix(const Vector3d &v)
{
    double vnormsq = v.dot(v);
    Matrix3d I;
    I.setIdentity();
    if(vnormsq == 0)
        return I;

    Matrix3d R = rotationMatrix(v);
    return (v*v.transpose() + (R.transpose()-I)*crossProductMatrix(v))/vnormsq;
}