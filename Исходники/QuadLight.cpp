QuadLight::QuadLight(const SpectralQuantity &intensity, const Vec3 &centre, const Vec3 &at_width, const Vec3 &at_height)
:	Light(intensity),
 	centre(centre),
 	at_width(at_width),
 	at_height(at_height)
{
    this->normal = at_height.cross(at_width);
    this->normal.normalize();

    width = at_width.length();
    this->at_width.normalize();

    height = at_height.length();
    this->at_height.normalize();
}