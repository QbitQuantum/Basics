Vec3f PhongMaterial::Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, const Vec3f &lightColor) const
{
    Vec3f eyeDir = ray.getDirection();
    eyeDir.Negate();

    Vec3f eyePlusLight = eyeDir + dirToLight;
    eyePlusLight.Normalize(); 
    
    float hn = eyePlusLight.Dot3(hit.getNormal());
    hn = pow(hn, mPhongComponent);

    Vec3f color = lightColor * mHighLightColor;
    color = hn * color;

    return color;
}