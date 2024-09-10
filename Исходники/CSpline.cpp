bool Spline::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}