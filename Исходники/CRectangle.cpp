bool Rectangle::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}