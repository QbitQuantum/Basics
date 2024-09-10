inline void Colour::setRed(double r)
{
    _r = clamp(r, 0.0, 1.0);
}