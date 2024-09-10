bool MxQuadric3::optimize(Vec3& v) const
{
    Mat3 Ainv;
    double det = invert(Ainv, tensor());
    if( FEQ(det, 0.0, 1e-12) )
	return false;

    v = -(Ainv*vector());

    return true;
}