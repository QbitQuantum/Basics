ClothoidPtr ClothoidFitter::getCurve() const
{
    Matrix4d lhs;

    lhs = _getLhs(_totalLength);

    Vector4d abcd = lhs.inverse() * _rhs;
    return getClothoidWithParams(abcd);
}