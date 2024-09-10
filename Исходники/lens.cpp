V2D Lens:: profile(const double alpha) const
{
    const double r     = Radius__(alpha);
    return V2D(r*Sin(alpha),Radius__(0)-r*Cos(alpha));
}