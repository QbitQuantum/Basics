Vector2F Vector2F::operator+(Vector2F& vec)
{
    Vector2F v (this->x + vec.getX(), this->y + vec.getY());
    return v;
}