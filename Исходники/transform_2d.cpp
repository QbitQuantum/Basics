bool Transform<Scalar, 2>::operator != (const Transform<Scalar, 2> &trans) const
{
    return !(this->rotate_angle_ == trans.rotateAngle() && this->translation_ == trans.translation() && this->scale_ == trans.scale());
}