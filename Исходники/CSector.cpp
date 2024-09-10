bool Sector::Intersects(const Vector2D& position) const {
    Vector2D l(this->GetPosition() - position);
    if(l.GetLength() > GetRadius()) return false;
    if(Math::IsEqual(l.GetLength(), 0.0)) return true;

    Vector2D sF = Vector2D::GetFacingVector(this->GetArcCenter(), this->GetPosition());
    Vector2D sF_n(sF.Normalize());
    Vector2D P_to_S(l.Normalize());

    double angle = std::acos(Vector2D::DotProduct(sF_n, P_to_S));

    return (angle <= GetTheta() / 2.0);
}